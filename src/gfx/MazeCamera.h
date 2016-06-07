//
// Created by Admin on 24/05/2016.
//

#pragma once

#include "Camera.h"
#include "../game/Maze.h"

namespace gfx {
    // TODO commentare classe
    class MazeCamera : public Camera {
    public:
        MazeCamera(game::Maze *maze) : maze_(maze), Camera() { }

        virtual void move(float incr);

        virtual void strafe(float incr);

        virtual void fly(float incr);

        game::Coordinates getMazeCoordinates();

        void setMaze(game::Maze *maze);

    private:
        game::Maze *maze_;

        bool checkBounds();

    };
}