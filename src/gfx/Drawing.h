#pragma once

#include <memory>
#include "../game/Maze.h"

namespace gfx {
    // Classe statica che fornisce le funzioni di disegno dei solidi OpenGL
    class Drawing {
    private:
        // Distanza massima dall'osservatore a cui viene renderizzato il labirinto (espressa in celle)
        static int drawDistance_;
    public:
        // Disegna il pavimento di una cella libera
        static void drawFloor(float x1, float x2, float y1, float z1, float z2);
        // Disegna il soffitto di una cella libera
        static void drawCeil(float x1, float x2, float y1, float z1, float z2);
        // Disegna una cella muro
        static void drawCube(float x1, float x2, float y1, float y2, float z1, float z2);
        // Disegna la porzione di labirinto circostante alla posizione passata per parametro
        static void drawMaze(std::shared_ptr<game::Maze> maze, int posX, int posY);
    };
}