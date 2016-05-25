//
// Created by Admin on 19/05/2016.
//

#pragma once


#include "Maze.h"

class MazeGenerator {
private:
    enum Direction {
        N, S, E, W
    };
public:
    static Maze* generateMaze(unsigned height, unsigned width);
};
