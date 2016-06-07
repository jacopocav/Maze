//
// Created by Admin on 24/05/2016.
//

#pragma once

#include <memory>
#include "Camera.h"
#include "../game/Maze.h"

namespace gfx {
    // TODO commentare classe
    class MazeCamera : public Camera {
    public:
        MazeCamera(std::shared_ptr<game::Maze> maze) : maze_(maze), Camera() { }

        virtual void move(float incr);

        virtual void strafe(float incr);

        virtual void fly(float incr);

        game::Coordinates getMazeCoordinates();

        void setMaze(std::shared_ptr<game::Maze> maze);

    private:
        std::shared_ptr<game::Maze> maze_;

        bool checkBounds();

    };
}