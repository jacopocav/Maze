#include <GL/glut.h>
#include <iostream>

#include "GlutUtils.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutUtils::Init();
    return 0;
}