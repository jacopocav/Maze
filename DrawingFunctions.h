//
// Created by Admin on 28/05/2016.
//

#pragma once


#include "Maze.h"

class DrawingFunctions {
private:
    static int draw_distance;
    static const float PI;
public:
    static void DrawFloor(float x1, float x2, float y1, float z1, float z2);
    static void DrawCeil(float x1, float x2, float y1, float z1, float z2);
    static void DrawCube(float x1, float x2, float y1, float y2, float z1, float z2);
    static void DrawMaze(Maze *maze, int pos_x, int pos_y);
};
