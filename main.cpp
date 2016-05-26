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
            out << (m->get(i,j) ? " " : "X");
        }
        out << "\n";
    }

    out.close();
    */
    glutInit(&argc, argv);
    GlutUtils::Init();
    return 0;
}

