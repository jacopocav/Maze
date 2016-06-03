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
    static void cullDeadEnd(Maze *maze, Coordinates cell);
public:
    static Maze* generateMaze(unsigned height, unsigned width);

    static void addAlarmsToMaze(Maze *maze, int alarmCount);


};
