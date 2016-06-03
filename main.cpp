#include <GL/glut.h>
#include <iostream>
#include <AL/alut.h>

#include "BigMess.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    alutInit(&argc, argv);
    BigMess::Init();
    return 0;
}