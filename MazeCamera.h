//
// Created by Admin on 24/05/2016.
//

#pragma once


#include "Camera.h"
#include "Maze.h"

class MazeCamera : public Camera {
public:
    MazeCamera(Maze *maze) : m_maze(maze), Camera() { }

    virtual void Move(float incr);

    virtual void Strafe(float incr);

    virtual void Fly(float incr);

    coordinates glCoordToMaze();

    void SetMaze(Maze* maze);

private:
    Maze *m_maze;

    bool checkBounds();

    void checkWinCondition();

};
