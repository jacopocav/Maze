#include <GL/glut.h>
#include <iostream>
#include <AL/alut.h>

#include "GlutFunctions.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    alutInit(&argc, argv);
    GlutFunctions::Init();
    return 0;
}