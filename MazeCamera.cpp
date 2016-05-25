//
// Created by Admin on 24/05/2016.
//

#include <cmath>
#include "MazeCamera.h"
#include "GlutUtils.h"
#include <GL/glut.h>
#include <string>

void MazeCamera::Move(float incr) {
    float lx = cos(m_yaw) * cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw) * cos(m_pitch);

    float old_x = m_x;
    float old_z = m_z;

    m_x = m_x + incr * lx;
    m_z = m_z + incr * lz;

    auto mazeCoord = glCoordToMaze();

    if ((!m_maze->operator()(mazeCoord) && m_y < 0.3 && m_y > -0.3) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.05f * lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.05f * lz;
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

    if ((!m_maze->operator()(mazeCoord) && m_y < 0.3 && m_y > -0.3) || !checkBounds()) {
        m_x = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.05f * m_strafe_lx;
        m_z = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.05f * m_strafe_lz;
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

std::pair<unsigned, unsigned> MazeCamera::glCoordToMaze() {
    /*int x = static_cast<unsigned>((m_x - (0.1 * sin(m_yaw * (M_PI / 180)))) / 0.4) + 1;
    int y = -1 * static_cast<unsigned>((m_z - (0.1 * cos(m_yaw * (M_PI / 180)))) / 0.4) + 1;
    */
    int x = static_cast<int>(std::round(m_x / 0.4)) + 1;
    int y = -1 * static_cast<int>(std::round(m_z / 0.4)) + 1;

    return std::pair<unsigned, unsigned>(x, y);
}

bool MazeCamera::checkBounds() {
    return m_x >= -0.6 && m_z <= 0.6 &&
           m_x <= (m_maze->getHeight() * 0.4 - 0.6) && m_z >= (-m_maze->getWidth() * 0.4 + 0.6);
}

bool MazeCamera::checkWinCondition() {
    auto mazeCoord = glCoordToMaze();
    std::pair<unsigned, unsigned> winCell(m_maze->getHeight() - 2, m_maze->getWidth() - 2);

    if (mazeCoord == winCell){
        glutSetWindowTitle("HAI VINTO!!!");
        GlutUtils::SetFPSMode(false);
    }
}