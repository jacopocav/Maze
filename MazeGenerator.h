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
    static std::pair<unsigned,unsigned> moveCell(std::pair<unsigned, unsigned> cell, Direction dir);
public:
    static Maze* generateMaze(unsigned height, unsigned width);
};
