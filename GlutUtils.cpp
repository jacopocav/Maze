//
// Created by Admin on 24/05/2016.
//
#include <sstream>
#include <iomanip>
#include "GlutUtils.h"
#include "TextureUtils.h"
#include "DrawingFunctions.h"


Maze *GlutUtils::m_maze;
MazeCamera GlutUtils::g_camera(nullptr);
int GlutUtils::currTime;
int GlutUtils::timeLimit;
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

const float GlutUtils::light_pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};

const float GlutUtils::g_translation_speed = 0.001;
const float GlutUtils::g_rotation_speed = Camera::M_PI / 180 * 0.15f;

const int GlutUtils::max_draw_distance = 15;

GLuint *GlutUtils::textureIDs = new GLuint[3];

GLubyte *GlutUtils::floorTexture = TextureUtils::ReadFromBMP("res/alt_floor.bmp");
GLubyte *GlutUtils::wallTexture = TextureUtils::ReadFromBMP("res/lux_wall.bmp");
GLubyte *GlutUtils::ceilTexture = TextureUtils::ReadFromBMP("res/alt_ceil2.bmp");

void GlutUtils::InitGame(){
    if(m_maze != nullptr) delete m_maze;
    m_maze = MazeGenerator::generateMaze(65, 65);

    g_camera.SetMaze(m_maze);
    g_camera.SetPos(0,0,0);
    g_camera.SetPitch(0);
    g_camera.SetYaw(0);

    timeLimit = 3 * 60 * 1000;
    currTime = glutGet(GLUT_ELAPSED_TIME);
}

void GlutUtils::Init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("SPAZIO per attivare/disattivare controlli FPS");

    glutIgnoreKeyRepeat(1);
    glClearColor(0, 0, 0, 1.0f);

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
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    GLfloat black[4] = {0, 0, 0, 1};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

    float ambient_light[4] = {0.8f, 0.8f, 0.8f, 1.0f};
    float diffuse_light[4] = {1.5f, 1.5f, 1.5f, 1.0f};
    float specular_light[4] = {2.0f, 2.0f, 2.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 2.0f);

    float material[4] = {1,1,1,1};
    glMaterialfv(GL_FRONT, GL_SPECULAR, material);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    glMateriali(GL_FRONT, GL_SHININESS, 56);

    glEnable(GL_TEXTURE_2D);

    glGenTextures(3, textureIDs);
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, wallTexture);


    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);

    glBindTexture(GL_TEXTURE_2D, textureIDs[2]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, ceilTexture);

    InitGame();

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

    coordinates pos = g_camera.glCoordToMaze();

    DrawingFunctions::DrawMaze(m_maze, pos.first, pos.second, textureIDs);

    glutSwapBuffers();
}


void GlutUtils::Reshape(int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport(0, 0, w, h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //set the perspective (angle of sight, width, height, ,depth)
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.001, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void GlutUtils::Keyboard(unsigned char key, int, int) {
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


    g_key[key] = true;
}

void GlutUtils::KeyboardUp(unsigned char key, int, int) {
    g_key[key] = false;
}

void GlutUtils::KeyboardSpecial(int key, int, int) {
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
        default:
            return;
    }
}

void GlutUtils::KeyboardSpecialUp(int key, int, int) {
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
        default:
            return;
    }
}


void GlutUtils::Timer(int) {
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    int timeDiff = newTime - currTime;
    currTime = newTime;
    if (g_fps_mode) {
        if (g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed * timeDiff);
        }
        else if (g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed * timeDiff);
        }
        if (g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed * timeDiff);
        }
        else if (g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed * timeDiff);
        }
        if (g_mouse_left_down) {
            g_camera.Fly(-2 * g_translation_speed * timeDiff);
        }
        else if (g_mouse_right_down) {
            g_camera.Fly(2 * g_translation_speed * timeDiff);
        }

        if (g_special_key[0]) {
            g_camera.RotatePitch(-g_rotation_speed * timeDiff);
        }
        else if (g_special_key[1]) {
            g_camera.RotatePitch(g_rotation_speed * timeDiff);
        }
        if (g_special_key[2]) {
            g_camera.RotateYaw(-g_rotation_speed * timeDiff);
        }
        else if (g_special_key[3]) {
            g_camera.RotateYaw(g_rotation_speed * timeDiff);
        }

        UpdateWindowTitle(timeDiff);
    }


    glutTimerFunc(16, Timer, 0);
}

void GlutUtils::UpdateWindowTitle(int timeDiff){
    coordinates pos = g_camera.glCoordToMaze();

    timeLimit -= timeDiff;

    std::stringstream windowTitle;

    if(timeLimit <= 0 || (pos.first == m_maze->getHeight() - 2 && pos.second == m_maze->getWidth() - 2)){
        if(timeLimit <= 0) windowTitle << "Tempo Scaduto! Hai perso!";
        else windowTitle << "Hai vinto!!!";
        windowTitle << " Premi SPAZIO per cominciare una nuova partita.";

        g_fps_mode = false;
        glutSetWindowTitle(windowTitle.str().c_str());
        InitGame();
    } else {
        windowTitle << "Tempo: ";
        windowTitle << std::setfill('0') << std::setw(2) << timeLimit / 60000;
        windowTitle << ":";
        windowTitle << std::setfill('0') << std::setw(2) << (timeLimit / 1000) % 60;
        windowTitle << ":";
        windowTitle << std::setfill('0') << std::setw(3) << timeLimit % 1000;

        windowTitle << "  Posizione: (";
        windowTitle << pos.first << ", ";
        windowTitle << pos.second << ")";
        glutSetWindowTitle(windowTitle.str().c_str());
    }
}

void GlutUtils::Idle() {
    Display();
}

void GlutUtils::Mouse(int button, int state, int, int) {
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
    delete wallTexture;
    delete floorTexture;
    delete ceilTexture;
    delete textureIDs;

}