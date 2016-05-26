//
// Created by Admin on 24/05/2016.
//

#include "GlutUtils.h"
#include "TextureUtils.h"
#include <GL/glut.h>

Maze *GlutUtils::m_maze = MazeGenerator::generateMaze(13, 13);
MazeCamera GlutUtils::g_camera(m_maze);
bool GlutUtils::g_key[256] = {};
bool GlutUtils::g_special_key[4] = {};
bool GlutUtils::g_fps_mode = false;
int GlutUtils::g_viewport_width = 0;
int GlutUtils::g_viewport_height = 0;
bool GlutUtils::g_mouse_left_down = false;
bool GlutUtils::g_mouse_right_down = false;

// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
// This avoids it being called recursively and hanging up the event loop
bool GlutUtils::just_warped = false;

float GlutUtils::light_pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};
float GlutUtils::ambient_light[4] = {0.5f, 0.5f, 0.5f, 1.0f};
float GlutUtils::diffuse_light[4] = {1.5f, 1.5f, 1.5f, 1.0f};
float GlutUtils::specular_light[4] = {2.0f, 2.0f, 2.0f, 1.0f};

float light_pos2[4] = {0.0f, 0.0f, 0.0f, 1.0f};
float ambient_light2[4] = {0.5f, 0.5f, 0.5f, 1.0f};
float diffuse_light2[4] = {0.0f, 1.5f, 0.0f, 1.0f};
float specular_light2[4] = {2.0f, 2.0f, 2.0f, 1.0f};

float GlutUtils::specular_material[4] = {1.0f, 1.0f, 1.0f, 1.0f};

const float GlutUtils::g_translation_speed = 0.015;
const float GlutUtils::g_rotation_speed = Camera::M_PI / 180 * 0.2f;
const float GlutUtils::g_keyboard_rotation_multiplier = 10.0;

//GLubyte *legno = TextureUtils::ReadFromFile("res/brick.bmp");

void GlutUtils::Init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SPAZIO per attivare/disattivare controlli FPS");

    glutIgnoreKeyRepeat(1);

    // Assegnazione callback
    glutDisplayFunc(GlutUtils::Display);
    glutIdleFunc(GlutUtils::Idle);
    glutReshapeFunc(GlutUtils::Reshape);
    glutMouseFunc(GlutUtils::Mouse);
    glutMotionFunc(GlutUtils::MouseMotion);
    glutPassiveMotionFunc(GlutUtils::MouseMotion);
    glutKeyboardFunc(GlutUtils::Keyboard);
    glutKeyboardUpFunc(GlutUtils::KeyboardUp);
    glutSpecialFunc(GlutUtils::KeyboardSpecial);
    glutSpecialUpFunc(GlutUtils::KeyboardSpecialUp);
    glutTimerFunc(16, GlutUtils::Timer, 0);


    // Configurazione camera
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    GLfloat black[4] = {0, 0, 0, 1};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.8f);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
    glMateriali(GL_FRONT, GL_SHININESS, 56);


    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, legno);
    glEnable(GL_TEXTURE_2D);*/

    glutMainLoop();
}


void GlutUtils::Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_camera.Refresh();

    float light_dir[3] = {0.0};
    g_camera.GetDirectionVector(light_dir[0], light_dir[1], light_dir[2]);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);

    glTranslatef(-0.6f, 0, 0.6);

    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glPopMatrix();

    DrawMaze();

    glutSwapBuffers();
}

void GlutUtils::DrawMaze() {
    for (int i = 0; i < m_maze->getHeight(); i++) {
        for (int j = 0; j < m_maze->getWidth(); j++) {
            if (m_maze->get(i, j) == 0)
                GlutUtils::DrawCube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else {
                bool winFloor = false;
                if (i == m_maze->getHeight() - 2 && j == m_maze->getWidth() - 2) winFloor = true;
                GlutUtils::DrawFloor(0.4f * i, 0.4f * (i + 1), -0.2f, -0.4f * j, -0.4f * (j + 1), winFloor);
                GlutUtils::DrawCeil(0.4f * i, 0.4f * (i + 1), 0.2f, -0.4f * j, -0.4f * (j + 1), winFloor);

            }
        }
    }
}


void GlutUtils::Reshape(int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport(0, 0, w, h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //set the perspective (angle of sight, width, height, ,depth)
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.001, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void GlutUtils::Keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        Cleanup();
        exit(0);
    }

    if (key == ' ') {
        g_fps_mode = !g_fps_mode;

        if (g_fps_mode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
    }

    g_key[key] = true;
}

void GlutUtils::KeyboardUp(unsigned char key, int x, int y) {
    g_key[key] = false;
}

void GlutUtils::KeyboardSpecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            g_special_key[0] = true;
            break;
        case GLUT_KEY_DOWN:
            g_special_key[1] = true;
            break;
        case GLUT_KEY_LEFT:
            g_special_key[2] = true;
            break;
        case GLUT_KEY_RIGHT:
            g_special_key[3] = true;
            break;
    }
}

void GlutUtils::KeyboardSpecialUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            g_special_key[0] = false;
            break;
        case GLUT_KEY_DOWN:
            g_special_key[1] = false;
            break;
        case GLUT_KEY_LEFT:
            g_special_key[2] = false;
            break;
        case GLUT_KEY_RIGHT:
            g_special_key[3] = false;
            break;
    }
}

void GlutUtils::Timer(int value) {
    if (g_fps_mode) {
        if (g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed);
        }
        else if (g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        if (g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if (g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        if (g_mouse_left_down) {
            g_camera.Fly(-2 * g_translation_speed);
        }
        else if (g_mouse_right_down) {
            g_camera.Fly(2 * g_translation_speed);
        }

        if (g_special_key[0]) {
            g_camera.RotatePitch(-g_rotation_speed * g_keyboard_rotation_multiplier);
        }
        else if (g_special_key[1]) {
            g_camera.RotatePitch(g_rotation_speed * g_keyboard_rotation_multiplier);
        }
        if (g_special_key[2]) {
            g_camera.RotateYaw(-g_rotation_speed * g_keyboard_rotation_multiplier);
        }
        else if (g_special_key[3]) {
            g_camera.RotateYaw(g_rotation_speed * g_keyboard_rotation_multiplier);
        }
    }

    glutTimerFunc(16, Timer, 0);
}

void GlutUtils::Idle() {
    Display();
}

void GlutUtils::Mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}

void GlutUtils::MouseMotion(int x, int y) {

    if (just_warped) {
        just_warped = false;
        return;
    }

    if (g_fps_mode) {
        int dx = x - g_viewport_width / 2;
        int dy = y - g_viewport_height / 2;

        if (dx) {
            g_camera.RotateYaw(g_rotation_speed * dx);
        }

        if (dy) {
            g_camera.RotatePitch(g_rotation_speed * dy);
        }

        glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

        just_warped = true;
    }
}

void GlutUtils::SetFPSMode(bool mode) {
    g_fps_mode = mode;
}

void GlutUtils::Cleanup() {
    delete m_maze;
}

void GlutUtils::DrawFloor(float x1, float x2, float y1, float z1, float z2, bool winFloor) {
    glBegin(GL_QUADS);

    if (winFloor) glColor3f(0.0, 1.0, 0.0);
    else glColor3f(0.0, 0.0, 0.1);
    glNormal3f(0, 1, 0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);

    glEnd();
}

void GlutUtils::DrawCeil(float x1, float x2, float y1, float z1, float z2, bool winFloor) {
    glBegin(GL_QUADS);

    if (winFloor) glColor3f(0.0, 1.0, 0.0);
    else glColor3f(0.0, 0.0, 0.1);
    glNormal3f(0, -1, 0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
}

void GlutUtils::DrawCube(float x1, float x2, float y1, float y2, float z1, float z2) {
    glBegin(GL_QUADS);

    //glColor3f(1.0, 1.0, 1.0); // Colore con texture
    glColor3f(1.5, 0.0, 0.0);
    glNormal3f(0, 0, -1);
    //glTexCoord2f(1, 1);
    //glColor3f(0.8, 0.0, 0.0);
    glVertex3f(x1, y1, z1);
    //glTexCoord2f(0, 1);
    glVertex3f(x2, y1, z1);
    //glColor3f(1.5, 0.0, 0.0);
    //glTexCoord2f(0, 0);
    glVertex3f(x2, y2, z1);
    //glTexCoord2f(1, 0);
    glVertex3f(x1, y2, z1);

    glNormal3f(0, 0, 1);
    //glColor3f(0.8, 0.0, 0.0);
    //glTexCoord2f(1, 1);
    glVertex3f(x1, y1, z2);
    //glColor3f(1.5, 0.0, 0.0);
    //glTexCoord2f(0, 1);
    glVertex3f(x1, y2, z2);
    //glTexCoord2f(0, 0);
    glVertex3f(x2, y2, z2);
    //glColor3f(0.8, 0.0, 0.0);
    //glTexCoord2f(1, 0);
    glVertex3f(x2, y1, z2);

    glNormal3f(0, 1, 0);
    //glColor3f(1.5, 0.0, 0.0);
    //glTexCoord2f(1, 1);
    glVertex3f(x1, y2, z1);
    //glTexCoord2f(0, 1);
    glVertex3f(x2, y2, z1);
    //glTexCoord2f(0, 0);
    glVertex3f(x2, y2, z2);
    //glTexCoord2f(1, 0);
    glVertex3f(x1, y2, z2);

    glNormal3f(1, 0, 0);
    //glColor3f(0.8, 0.0, 0.0);
    //glTexCoord2f(1, 1);
    glVertex3f(x1, y1, z1);
    //glColor3f(1.5, 0.0, 0.0);
    //glTexCoord2f(0, 1);
    glVertex3f(x1, y2, z1);
    //glTexCoord2f(0, 0);
    glVertex3f(x1, y2, z2);
    //glColor3f(0.8, 0.0, 0.0);
    //glTexCoord2f(1, 0);
    glVertex3f(x1, y1, z2);

    glNormal3f(-1, 0, 0);
    //glColor3f(0.8, 0.0, 0.0);
    //glTexCoord2f(1, 1);
    glVertex3f(x2, y1, z1);
    //glTexCoord2f(0, 1);
    glVertex3f(x2, y1, z2);
    //glTexCoord2f(0, 0);
    //glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x2, y2, z2);
    //glTexCoord2f(1, 0);
    glVertex3f(x2, y2, z1);
    //glColor3f(0.8, 0.0, 0.0);


    glEnd();
}