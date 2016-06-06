#include <GL/glut.h>
#include <iostream>

#include "GlutCallbacks.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutCallbacks::init();
    return 0;
}