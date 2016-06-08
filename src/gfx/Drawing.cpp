//
// Created by Admin on 28/05/2016.
//

#include <GL/gl.h>
#include <cmath>
#include "Drawing.h"
#include "Textures.h"
#include "../game/Settings.h"
#include "Camera.h"
#include "../game/Time.h"

int gfx::Drawing::drawDistance_ = game::Settings::getInstance()["DRAW_DISTANCE"];

void gfx::Drawing::drawFloor(float x1, float x2, float y1, float z1, float z2) {
    Textures::useTexture("floor"); // Usa la texture "pavimento"
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
    Textures::useTexture("0");
}

void gfx::Drawing::drawCeil(float x1, float x2, float y1, float z1, float z2) {
    Textures::useTexture("ceil"); // Usa la texture "soffitto"
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
    Textures::useTexture("0");
}

void gfx::Drawing::drawCube(float x1, float x2, float y1, float y2, float z1, float z2) {

    Textures::useTexture("wall"); // Usa la texture "muro"
    glBegin(GL_QUADS);
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

    glNormal3f(0, 1, 0);
    glVertex3f(x1, y2, z1);
    glNormal3f(0, 1, 0);
    glVertex3f(x2, y2, z1);
    glNormal3f(0, 1, 0);
    glVertex3f(x2, y2, z2);
    glNormal3f(0, 1, 0);
    glVertex3f(x1, y2, z2);

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
    Textures::useTexture("0");

}


void gfx::Drawing::drawMaze(std::shared_ptr<game::Maze> maze, int posX, int posY) {
    int min_x = 0, max_x = maze->getHeight(), min_y = 0, max_y = maze->getWidth();

    if ((posX - drawDistance_) > min_x)
        min_x = posX - drawDistance_;
    if ((posX + drawDistance_) < max_x)
        max_x = posX + drawDistance_;
    if ((posY - drawDistance_) > min_y)
        min_y = posY - drawDistance_;
    if ((posY + drawDistance_) < max_y)
        max_y = posY + drawDistance_;

    for (int i = min_x; i < max_x; i++) {
        for (int j = min_y; j < max_y; j++) {
            if (!maze->get(i, j)) // La cella è un muro, disegna un cubo
                drawCube(0.4f * i, 0.4f * (i + 1), -0.2f, 0.2, -0.4f * j, -0.4f * (j + 1));
            else { // La cella è libera
                if (maze->isAlarm(static_cast<unsigned>(i), static_cast<unsigned>(j))) { // C'è un allarme nella cella
                    Textures::useTexture("0");

                    // Usa il tempo per animare l'oggetto allarme
                    // milliTime va continuamente da 0 a 0.999
                    float milliTime = (game::Time::getCurrentTimeMillis() % 1000) / 1000.0f;

                    // Colore rosso pulsante
                    float mat[4] = {2.0f - (0.7f * (1 - cosf(2 * milliTime * constants::PI))), 0.0f, 0.0f, 1};
                    float material[4] = {1, 1, 1, 1};
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
                    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
                    glPushMatrix();
                    glTranslatef(0.4f * i + 0.2f, 0, -0.4f * j - 0.2f);
                    // Anello rotante
                    glRotatef(milliTime * 180, 0.0f, 1.0f, 0.0f);
                    glutSolidTorus(0.01f, 0.06f, 64, 64);
                    // Sfera "pulsante" (si ingrandisce e riduce ritmicamente) al centro dell'anello
                    glutSolidSphere(0.02f + (0.02f * 0.5f * (1 + cosf(2 * milliTime * constants::PI))), 64, 64);
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