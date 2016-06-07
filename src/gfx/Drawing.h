//
// Created by Admin on 28/05/2016.
//

#pragma once


#include <memory>
#include "../game/Maze.h"
namespace gfx {
    // TODO commentare classe
    class Drawing {
    private:
        static int drawDistance_;
        static const float PI;
    public:
        static void drawFloor(float x1, float x2, float y1, float z1, float z2);

        static void drawCeil(float x1, float x2, float y1, float z1, float z2);

        static void drawCube(float x1, float x2, float y1, float y2, float z1, float z2);

        static void drawMaze(std::shared_ptr<game::Maze> maze, int pos_x, int pos_y);
    };
}