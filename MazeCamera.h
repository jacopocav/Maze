//
// Created by Admin on 24/05/2016.
//

#pragma once


#include "Camera.h"
#include "Maze.h"

class MazeCamera : public Camera {
public:
    MazeCamera(Maze *maze) : m_maze(maze), m_last_valid_x(-0.6f), m_last_valid_z(0.6f), Camera() { }

    virtual void Move(float incr);

    virtual void Strafe(float incr);

    virtual void Fly(float incr);


private:
    Maze *m_maze;

    std::pair<unsigned, unsigned> glCoordToMaze();

    bool checkBounds();

    float m_last_valid_x, m_last_valid_z;

    bool checkWinCondition();

};
