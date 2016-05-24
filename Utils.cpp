//
// Created by Admin on 24/05/2016.
//

#include "Utils.h"
#include <GL/glut.h>


void Utils::floor(float x1, float x2, float y1, float z1, float z2){
    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 0.2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);

    glEnd();
}
void Utils::cube(float x1, float x2, float y1, float y2, float z1, float z2){
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