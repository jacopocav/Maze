//
// Created by Admin on 28/05/2016.
//

#include <GL/gl.h>
#include "DrawingFunctions.h"
#include "TextureUtils.h"

int DrawingFunctions::draw_distance = 15;

void DrawingFunctions::DrawFloor(float x1, float x2, float y1, float z1, float z2) {
    TextureUtils::BindTexture("floor");
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

void DrawingFunctions::DrawCeil(float x1, float x2, float y1, float z1, float z2) {
    TextureUtils::BindTexture("ceil");

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

void DrawingFunctions::DrawCube(float x1, float x2, float y1, float y2, float z1, float z2) {

    TextureUtils::BindTexture("wall");
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
    TextureUtils::BindTexture("0");

}


void DrawingFunctions::DrawMaze(Maze *maze, int pos_x, int pos_y) {
    int min_x = 0, max_x = maze->getHeight(), min_y = 0, max_y = maze->getWidth();

    if ((pos_x - draw_distance) > min_x)
        min_x = pos_x - draw_distance;
    if ((pos_x + draw_distance) < max_x)
        max_x = pos_x + draw_distance;
    if ((pos_y - draw_distance) > min_y)
        min_y = pos_y - draw_distance;
    if ((pos_y + draw_distance) < max_y)
        max_y = pos_y + draw_distance;


    for (int i = min_x; i < max_x; i++) {
        for (int j = min_y; j < max_y; j++) {
            if (!maze->get(i, j))
                DrawCube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else {
                if (maze->isAlarm(static_cast<unsigned>(i), static_cast<unsigned>(j))) {
                    TextureUtils::BindTexture("0");
                    float mat[4] = {1, 0, 0, 1};
                    float material[4] = {1, 1, 1, 1};
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
                    glPushMatrix();
                    glTranslatef(0.4f * i + 0.2f, 0, -0.4f * j - 0.2f);
                    glutSolidSphere(0.025f, 32, 32);
                    glPopMatrix();
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, material);

                }
                DrawFloor(0.4f * i, 0.4f * (i + 1), -0.2f, -0.4f * j, -0.4f * (j + 1));
                DrawCeil(0.4f * i, 0.4f * (i + 1), 0.2f, -0.4f * j, -0.4f * (j + 1));

            }
        }
    }
}