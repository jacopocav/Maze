//
// Created by Admin on 24/05/2016.
//

#include "GlutUtils.h"
#include <GL/glut.h>

Maze *GlutUtils::m_maze = MazeGenerator::generateMaze(65, 65);
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

const float GlutUtils::g_translation_speed = 0.015;
const float GlutUtils::g_rotation_speed = Camera::M_PI / 180 * 0.2f;
const float GlutUtils::g_keyboard_rotation_multiplier = 10.0;

void GlutUtils::DrawFloor(float x1, float x2, float y1, float z1, float z2, bool winFloor) {
    glBegin(GL_QUADS);

    if (winFloor) glColor3f(0.0, 1.0, 0.0);
    else glColor3f(0.05, 0.0, 0.0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
}

void GlutUtils::DrawCube(float x1, float x2, float y1, float y2, float z1, float z2) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonOffset(-1.5f, -1.5f);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glBegin(GL_QUADS);

    glColor3f(0.05, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y1, z2);

    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
    glDisable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_QUADS);

    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x1, y1, z1);
    glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);
    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x1, y1, z2);

    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x2, y1, z1);
    glColor3f(1.5, 0.0, 0.0);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glColor3f(0.1, 0.0, 0.0);
    glVertex3f(x2, y1, z2);

    glEnd();
}

void GlutUtils::Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_camera.Refresh();

    glRotatef(0.0, 0.0, 1.0, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);

    glTranslatef(-0.6f, 0, 0.6);


    for (int i = 0; i < m_maze->getHeight(); i++) {
        for (int j = 0; j < m_maze->getWidth(); j++) {
            if (m_maze->get(i, j) == 0)
                GlutUtils::DrawCube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else {
                bool winFloor = false;
                if (i == m_maze->getHeight() - 2 && j == m_maze->getWidth() - 2) winFloor = true;
                GlutUtils::DrawFloor(0.4f * i, 0.4f * (i + 1), -0.2f, -0.4f * j, -0.4f * (j + 1), winFloor);
                GlutUtils::DrawFloor(0.4f * i, 0.4f * (i + 1), 0.2f, -0.4f * j, -0.4f * (j + 1), winFloor);

            }
        }
    }
    glutSwapBuffers();
}

void GlutUtils::Reshape(int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection

    glLoadIdentity();

    //set the perspective (angle of sight, width, height, ,depth)
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.001, 50.0);
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
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

void GlutUtils::Cleanup(){
    delete m_maze;
}