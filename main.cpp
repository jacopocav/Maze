/*
FPS control demo in GLUT by Nghia Ho

SPACEBAR - toggle FPS control
W,A,S,D - to move
mouse - look around, inverted mouse
left/right mouse - fly up/down
ESC - quit

*/

#include <GL/glut.h>
#include <iostream>

#include "GlutUtils.h"

using namespace std;


int main(int argc, char **argv) {

    /*std::ofstream out;
    out.open("D:\\Desktop\\maze.txt");

    for (int i = 0; i < m->getHeight(); ++i) {
        for (int j = 0; j < m->getWidth(); ++j) {
            out << (m->operator()(i,j) ? " " : "X");
        }
        out << "\n";
    }

    out.close();
    */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SPAZIO per attivare/disattivare controlli FPS");

    //glutIgnoreKeyRepeat(1);

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

    glutMainLoop();

    return 0;
}

