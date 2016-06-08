#include <cmath>
#include "MazeCamera.h"

void gfx::MazeCamera::move(float incr) {
    float lx = cosf(yaw_) * cosf(pitch_);
    float lz = sinf(yaw_) * cosf(pitch_);

    float old_x = x_;
    float old_z = z_;

    x_ = x_ + incr * lx;
    z_ = z_ + incr * lz;

    auto mazeCoord = getMazeCoordinates();

    // Se la camera è finita in una cella muro o ha oltrepassato i bordi del labirinto,
    // si "rimbalza" indietro
    if ((!maze_->get(mazeCoord) && y_ < 0.2 && y_ > -0.2) || !checkBounds()) {
        x_ = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lx;
        z_ = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * lz;
    }

    refresh();
}

void gfx::MazeCamera::strafe(float incr) {
    float old_x = x_;
    float old_z = z_;

    x_ = x_ + incr * strafeLx_;
    z_ = z_ + incr * strafeLz_;

    auto mazeCoord = getMazeCoordinates();

    // Idem
    if ((!maze_->get(mazeCoord) && y_ < 0.2 && y_ > -0.2) || !checkBounds()) {
        x_ = old_x - 1 * ((incr > 0) - (incr < 0)) * 0.01f * strafeLx_;
        z_ = old_z - 1 * ((incr > 0) - (incr < 0)) * 0.01f * strafeLz_;
    }

    refresh();
}

void gfx::MazeCamera::fly(float incr) {
    auto mazeCoord = getMazeCoordinates();
    y_ += incr;

    if (!maze_->get(mazeCoord) && y_ < 0.25) y_ = 0.25; // Impedisce di volare dentro ad un muro
    else if (y_ < 0) y_ = 0; // Impedisce di volare sotto al pavimento

    refresh();
}

void gfx::MazeCamera::setMaze(std::shared_ptr<game::Maze> maze) {
    maze_ = maze;
}

game::Coordinates gfx::MazeCamera::getMazeCoordinates() {
    int x = static_cast<int>(std::round(x_ / 0.4)) + 1;
    int y = -1 * static_cast<int>(std::round(z_ / 0.4)) + 1;

    return game::Coordinates(x, y);
}

bool gfx::MazeCamera::checkBounds() {
    return x_ > -0.5 && z_ < 0.5 &&
           x_ <= ((maze_->getHeight() - 1) * 0.4 - 0.2) - 0.1 &&
           z_ >= (-(maze_->getWidth() - 1) * 0.4 + 0.2) + 0.1;
}