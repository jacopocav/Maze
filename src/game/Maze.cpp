//
// Created by Admin on 19/05/2016.
//

#include <cstdlib>
#include <algorithm>
#include "Maze.h"

int game::Maze::getHeight() const {
    return maze_.size();
}

int game::Maze::getWidth() const {
    return maze_[0].size();
}

bool game::Maze::get(int row, int col) const {
    return maze_[row][col];
}

game::Maze::Maze(unsigned height, unsigned width) : start_(1, 1), end_(height - 2, width - 2), alarms_() {
    if (height % 2 == 0) height++;
    if (width % 2 == 0) width++;

    maze_.resize(height);
    for (auto i = 0; i < height; ++i) {
        maze_[i].assign(width, false);
    }

    wasHere_.resize(height);
    for (auto i = 0; i < height; ++i) {
        wasHere_[i].assign(width, false);
    }
}

bool game::Maze::get(game::Coordinates coord) const {
    return get(coord.first, coord.second);
}

void game::Maze::set(game::Coordinates coord, bool val) {
    set(coord.first, coord.second, val);
}

void game::Maze::set(int row, int col, bool val) {
    maze_[row][col] = val;
}

int correctPathLength = 0;

int game::Maze::pathLength(int startX, int startY, int endX, int endY) {
    correctPathLength = 0;
    for(int i = 0; i < wasHere_.size(); ++i){
        wasHere_[i].assign(wasHere_[i].size(), false);
    }
    recursiveSolve(startX, startY, endX, endY);
    // Will leave you with a boolean array (correctPath)
    // with the path indicated by true values.
    // If b is false, there is no solution to the maze_
    return correctPathLength;
}

bool game::Maze::recursiveSolve(int x, int y, int endX, int endY) {
    if (x == endX && y == endY) return true; // If you reached the end
    if (!maze_[x][y] || wasHere_[x][y]) return false;
    // If you are on a wall or already were here
    wasHere_[x][y] = true;
    if (x != 0) // Checks if not on left edge
    if (recursiveSolve(x - 1, y, endX, endY)) { // Recalls method one to the left
        correctPathLength++; // Sets that path value to true;
        return true;
    }
    if (x != maze_.size() - 1) // Checks if not on right edge
    if (recursiveSolve(x + 1, y, endX, endY)) { // Recalls method one to the right
        correctPathLength++;
        return true;
    }
    if (y != 0)  // Checks if not on top edge
    if (recursiveSolve(x, y - 1, endX, endY)) { // Recalls method one up
        correctPathLength++;
        return true;
    }
    if (y != maze_[0].size() - 1) // Checks if not on bottom edge
    if (recursiveSolve(x, y + 1, endX, endY)) { // Recalls method one down
        correctPathLength++;
        return true;
    }
    return false;
}

void game::Maze::setAlarm(game::Coordinates pos) {
    if(!isAlarm(pos))
        alarms_.push_back(pos);
}

bool game::Maze::isAlarm(game::Coordinates pos) const {
    return std::find(alarms_.begin(), alarms_.end(), pos) != alarms_.end();
}

bool game::Maze::isAlarm(unsigned row, unsigned col) const {
    return std::find(alarms_.begin(), alarms_.end(), std::make_pair(row, col)) != alarms_.end();
}

void game::Maze::removeAlarm(game::Coordinates pos) {
    auto it = std::find(alarms_.begin(), alarms_.end(), pos);
    if(it != alarms_.end()) {
        *it = alarms_.back();
        alarms_.pop_back();
    }
}

int game::Maze::getAlarmCount() const {
    return alarms_.size();
}

game::Coordinates game::Maze::getAlarm(int index) {
    if(index >= 0 && index < getAlarmCount()){
        return alarms_[index];
    }
    return std::make_pair(-1, -1);
}









