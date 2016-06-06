//
// Created by Admin on 28/05/2016.
//

#include <GL/gl.h>
#include <cmath>
#include "Drawing.h"
#include "Textures.h"
#include "../game/Settings.h"

int gfx::Drawing::drawDistance_ = game::Settings::getInstance()["DRAW_DISTANCE"];
const float gfx::Drawing::PI = 3.14159265358979323846f;

void gfx::Drawing::drawFloor(float x1, float x2, float y1, float z1, float z2) {
    Textures::bindTexture("floor");
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);

    glNormal3f(0, 1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(x2, y1, z1);
    glNormal3f(0, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x2, y1, z2);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 1);
    glVertex3f(x1, y1, z2);
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(x1, y1, z1);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void gfx::Drawing::drawCeil(float x1, float x2, float y1, float z1, float z2) {
    Textures::bindTexture("ceil");
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);

    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(x1, y1, z1);
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x1, y1, z2);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 1);
    glVertex3f(x2, y1, z2);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(x2, y1, z1);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void gfx::Drawing::drawCube(float x1, float x2, float y1, float y2, float z1, float z2) {

    Textures::bindTexture("wall");
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    //glColor3f(1,0,0);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 0);
    glNormal3f(0, 0, 1);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1, 1);
    glNormal3f(0, 0, 1);
    glVertex3f(x2, y2, z1);
    glTexCoord2f(0, 1);
    glNormal3f(0, 0, 1);
    glVertex3f(x1, y2, z1);

    //glColor3f(0,1,0);
    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 0);
    glVertex3f(x1, y1, z2);
    glTexCoord2f(1, 1);
    glNormal3f(0, 0, -1);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(0, 1);
    glNormal3f(0, 0, -1);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(0, 0);
    glNormal3f(0, 0, -1);
    glVertex3f(x2, y1, z2);

    //glColor3f(0,0,1);
    glNormal3f(0, 1, 0);
    glVertex3f(x1, y2, z1);
    glNormal3f(0, 1, 0);
    glVertex3f(x2, y2, z1);
    glNormal3f(0, 1, 0);
    glVertex3f(x2, y2, z2);
    glNormal3f(0, 1, 0);
    glVertex3f(x1, y2, z2);

    //glColor3f(1,1,0);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(1, 0);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(1, 1);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y2, z1);
    glTexCoord2f(0, 1);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y2, z2);
    glTexCoord2f(0, 0);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y1, z2);

    //glColor3f(1,0,1);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(x2, y1, z1);
    glTexCoord2f(1, 0);
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(1, 1);
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(0, 1);
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y2, z1);


    glEnd();
    Textures::bindTexture("0");

}


void gfx::Drawing::drawMaze(game::Maze *maze, int pos_x, int pos_y) {
    int min_x = 0, max_x = maze->getHeight(), min_y = 0, max_y = maze->getWidth();

    if ((pos_x - drawDistance_) > min_x)
        min_x = pos_x - drawDistance_;
    if ((pos_x + drawDistance_) < max_x)
        max_x = pos_x + drawDistance_;
    if ((pos_y - drawDistance_) > min_y)
        min_y = pos_y - drawDistance_;
    if ((pos_y + drawDistance_) < max_y)
        max_y = pos_y + drawDistance_;

    for (int i = min_x; i < max_x; i++) {
        for (int j = min_y; j < max_y; j++) {
            if (!maze->get(i, j))
                drawCube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else {
                if (maze->isAlarm(static_cast<unsigned>(i), static_cast<unsigned>(j))) {
                    Textures::bindTexture("0");
                    float time = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) / 1000;
                    int intime = static_cast<int>(time);
                    time = time - intime;
                    float mat[4] = {2.0f-(0.7f * (1-cosf(2*time*PI))), 0.0f, 0.0f, 1};
                    float material[4] = {1, 1, 1, 1};
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
                    glPushMatrix();
                    glTranslatef(0.4f * i + 0.2f, 0, -0.4f * j - 0.2f);
                    glRotatef(time*180, 0.0f, 1.0f, 0.0f);
                    glutSolidTorus(0.01f, 0.06f, 64, 64);
                    glutSolidSphere(0.02f + (0.02f * 0.5f * (1+cosf(2*time*PI))), 64, 64);
                    glPopMatrix();
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, material);

                }
                drawFloor(0.4f * i, 0.4f * (i + 1), -0.2f, -0.4f * j, -0.4f * (j + 1));
                drawCeil(0.4f * i, 0.4f * (i + 1), 0.2f, -0.4f * j, -0.4f * (j + 1));

            }
        }
    }
}