/*
FPS control demo in GLUT by Nghia Ho

SPACEBAR - toggle FPS control
W,A,S,D - to move
mouse - look around, inverted mouse
left/right mouse - fly up/down
ESC - quit

*/

#include <GL/freeglut.h>
#include <iostream>

#include "Camera.h"
#include "Maze.h"
#include "MazeGenerator.h"

using namespace std;

void Display();

void Reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);

void KeyboardUp(unsigned char key, int x, int y);

void MouseMotion(int x, int y);

void Mouse(int button, int state, int x, int y);

void Timer(int value);

void Idle();

void Grid();

Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

// Movement settings
const float g_translation_speed = 0.002;
const float g_rotation_speed = Camera::M_PI / 180 * 0.2f;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("FPS demo by Nghia Ho - Hit SPACEBAR to toggle FPS mode");

    glutIgnoreKeyRepeat(1);


    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MouseMotion);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutIdleFunc(Idle);

    glutTimerFunc(1, Timer, 0);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity ();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutMainLoop();

    return 0;
}

void Grid() {
    glPushMatrix();
    glColor3f(1, 1, 1);

    for (int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for (int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
}

float ang = 0.0;
float ang2 = 0.0;
float f = -5.0f;
float f2 = 0.0;
float f3 = 0.0;

void floor(float x1, float x2, float y1, float z1, float z2){
    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 0.2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
}
void cube(float x1, float x2, float y1, float y2, float z1, float z2){
    glBegin(GL_QUADS);

    glColor3f(8.3, 0.2, 0.0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glColor3f(1.3, 7.2, 0.0);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);

    glColor3f(0.3, 9.2, 2.0);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glColor3f(1.3, 0.2, 9.0);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glColor3f(0.3, 7.2, 0.0);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glColor3f(0.3, 0.2, 9.0);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);

    glColor3f(0.3, 0.2, 8.0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glColor3f(8.3, 0.2, 2.0);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y1, z2);

    glColor3f(0.3, 0.2, 8.0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glColor3f(9.3, 0.2, 0.0);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
}

Maze *m = MazeGenerator::generateMaze(13, 13);

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_camera.Refresh();

    //Grid();

    /*glColor3f(1, 0, 0);
    glutSolidCube(1);*/

    //glutSwapBuffers(); //swap the buffers

    glRotatef(ang,0.0,1.0,0.0);
    glRotatef(ang2,1.0,0.0,0.0);

    glTranslatef(-0.6f,0, 0.6);


    int i, j;
    for(i = 0 ; i < m->getHeight(); i++){
        for(j = 0 ; j < m->getWidth(); j++){
            if(m->operator()(i,j) == 0) cube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else floor(0.4f * i, 0.4f * (i + 1), -0.2f, -0.4f * j, -0.4f * (j + 1));
        }
    }
    glutSwapBuffers();
}

void Reshape(int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection

    glLoadIdentity();
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.1,
                   200.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void Keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
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
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }

    g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y) {
    g_key[key] = false;
}

void Timer(int value) {
    if (g_fps_mode) {
        if (g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed);
        }
        else if (g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        else if (g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if (g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        else if (g_mouse_left_down) {
            g_camera.Fly(-g_translation_speed);
        }
        else if (g_mouse_right_down) {
            g_camera.Fly(g_translation_speed);
        }
    }

    glutTimerFunc(1, Timer, 0);
}

void Idle() {
    Display();
}

void Mouse(int button, int state, int x, int y) {
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

void MouseMotion(int x, int y) {
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

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

