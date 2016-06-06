//
// Created by Admin on 05/06/2016.
//

#pragma once

#include "Maze.h"

namespace game {

    class Time {
    public:
        static int getTimeLimit(Maze *maze, game::Coordinates currentPos);
        static int manhattanDistance(game::Coordinates pos1, game::Coordinates pos2);
        static int getCurrentTimeMillis();
    };

}
