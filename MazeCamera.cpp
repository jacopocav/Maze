//
// Created by Admin on 24/05/2016.
//

#include <cmath>
#include "MazeCamera.h"
#include "GlutUtils.h"
#include <GL/glut.h>
#include <string>

void MazeCamera::Move(float incr) {
    float lx = cosf(m_yaw) * cosf(m_pitch);
    float lz = sinf(m_yaw) * cosf(m_pitch);

    float old_x = m_x;
    float old_z = m_z;

    m_x = m_x + incr * lx;
    m_z = m_z + incr * lz;

    auto mazeCoord = glCoordToMaze();

    if ((!m_maze->get(mazeCoord) && m_y < 0.2 && m_y > -0.2) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lz;
    }

    std::string pos("x:[");
    pos.append(std::to_string(mazeCoord.first));
    pos.append("] z:[");
    pos.append(std::to_string(mazeCoord.second));
    pos.append("]");

    glutSetWindowTitle(pos.c_str());

    Refresh();
    checkWinCondition();
}

void MazeCamera::Strafe(float incr) {
    float old_x = m_x;
    float old_z = m_z;

    m_x = m_x + incr * m_strafe_lx;
    m_z = m_z + incr * m_strafe_lz;

    auto mazeCoord = glCoordToMaze();

    if ((!m_maze->get(mazeCoord) && m_y < 0.2 && m_y > -0.2) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * m_strafe_lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * m_strafe_lz;
    }

    std::string pos("x:[");
    pos.append(std::to_string(mazeCoord.first));
    pos.append("] z:[");
    pos.append(std::to_string(mazeCoord.second));
    pos.append("]");

    glutSetWindowTitle(pos.c_str());

    Refresh();
    checkWinCondition();
}

void MazeCamera::Fly(float incr) {
    Camera::Fly(incr);
}

coordinates MazeCamera::glCoordToMaze() {
    int x = static_cast<int>(std::round(m_x / 0.4)) + 1;
    int y = -1 * static_cast<int>(std::round(m_z / 0.4)) + 1;

    return coordinates(x, y);
}

bool MazeCamera::checkBounds() {
    return m_x >= -0.6 && m_z <= 0.6 &&
           m_x <= (m_maze->getHeight() * 0.4 - 0.6) && m_z >= (-m_maze->getWidth() * 0.4 + 0.6);
}

void MazeCamera::checkWinCondition() {
    auto mazeCoord = glCoordToMaze();
    coordinates winCell(m_maze->getHeight() - 2, m_maze->getWidth() - 2);

    if (mazeCoord == winCell) {
        glutSetWindowTitle("HAI VINTO!!!");
        GlutUtils::SetFPSMode(false);
    }
}