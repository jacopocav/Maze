//
// Created by Admin on 24/05/2016.
//

#include <cmath>
#include "MazeCamera.h"
#include "BigMess.h"
#include <GL/glut.h>
#include <string>

void MazeCamera::Move(float incr) {
    float lx = cosf(m_yaw) * cosf(m_pitch);
    float lz = sinf(m_yaw) * cosf(m_pitch);

    float old_x = m_x;
    float old_z = m_z;

    m_x = m_x + incr * lx;
    m_z = m_z + incr * lz;

    auto mazeCoord = getMazeCoordinates();

    if ((!m_maze->get(mazeCoord) && m_y < 0.2 && m_y > -0.2) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lz;
    }

    Refresh();
}

void MazeCamera::Strafe(float incr) {
    float old_x = m_x;
    float old_z = m_z;

    m_x = m_x + incr * m_strafe_lx;
    m_z = m_z + incr * m_strafe_lz;

    auto mazeCoord = getMazeCoordinates();


    if ((!m_maze->get(mazeCoord) && m_y < 0.2 && m_y > -0.2) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * m_strafe_lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * m_strafe_lz;
    }

    Refresh();
}

void MazeCamera::Fly(float incr) {
    m_y += incr;
    if (m_y < 0) m_y = 0;

    Refresh();
}

void MazeCamera::SetMaze(Maze *maze) {
    m_maze = maze;
}

Coordinates MazeCamera::getMazeCoordinates() {
    int x = static_cast<int>(std::round(m_x / 0.4)) + 1;
    int y = -1 * static_cast<int>(std::round(m_z / 0.4)) + 1;

    return Coordinates(x, y);
}

bool MazeCamera::checkBounds() {
    return m_x > -0.5 && m_z < 0.5 &&
           m_x <= ((m_maze->getHeight() - 1) * 0.4 - 0.2) - 0.1 && m_z >= (-(m_maze->getWidth() - 1) * 0.4 +0.2) + 0.1;
}