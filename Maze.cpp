//
// Created by Admin on 19/05/2016.
//

#include <cstdlib>
#include <algorithm>
#include "Maze.h"

int Maze::getHeight() const {
    return maze.size();
}

int Maze::getWidth() const {
    return maze[0].size();
}

bool Maze::get(int row, int col) const {
    return maze[row][col];
}

Maze::Maze(unsigned height, unsigned width) : start(1, 1), end(height - 2, width - 2), alarms() {
    if (height % 2 == 0) height++;
    if (width % 2 == 0) width++;

    maze.resize(height);
    for (auto i = 0; i < height; ++i) {
        maze[i].assign(width, false);
    }

    wasHere.resize(height);
    for (auto i = 0; i < height; ++i) {
        wasHere[i].assign(width, false);
    }
}

bool Maze::get(Coordinates coord) const {
    return get(coord.first, coord.second);
}

void Maze::set(Coordinates coord, bool val) {
    set(coord.first, coord.second, val);
}

void Maze::set(int row, int col, bool val) {
    maze[row][col] = val;
}

int correctPathLength = 0;

int Maze::solve(int startX, int startY, int endX, int endY) {
    correctPathLength = 0;
    for(int i = 0; i < wasHere.size(); ++i){
        wasHere[i].assign(wasHere[i].size(), false);
    }
    recursiveSolve(startX, startY, endX, endY);
    // Will leave you with a boolean array (correctPath)
    // with the path indicated by true values.
    // If b is false, there is no solution to the maze
    return correctPathLength;
}

bool Maze::recursiveSolve(int x, int y, int endX, int endY) {
    if (x == endX && y == endY) return true; // If you reached the end
    if (!maze[x][y] || wasHere[x][y]) return false;
    // If you are on a wall or already were here
    wasHere[x][y] = true;
    if (x != 0) // Checks if not on left edge
    if (recursiveSolve(x - 1, y, endX, endY)) { // Recalls method one to the left
        correctPathLength++; // Sets that path value to true;
        return true;
    }
    if (x != maze.size() - 1) // Checks if not on right edge
    if (recursiveSolve(x + 1, y, endX, endY)) { // Recalls method one to the right
        correctPathLength++;
        return true;
    }
    if (y != 0)  // Checks if not on top edge
    if (recursiveSolve(x, y - 1, endX, endY)) { // Recalls method one up
        correctPathLength++;
        return true;
    }
    if (y != maze[0].size() - 1) // Checks if not on bottom edge
    if (recursiveSolve(x, y + 1, endX, endY)) { // Recalls method one down
        correctPathLength++;
        return true;
    }
    return false;
}

void Maze::setAlarm(Coordinates pos) {
    if(!isAlarm(pos))
        alarms.push_back(pos);
}

bool Maze::isAlarm(Coordinates pos) const {
    return std::find(alarms.begin(), alarms.end(), pos) != alarms.end();
}

bool Maze::isAlarm(unsigned row, unsigned col) const {
    return std::find(alarms.begin(), alarms.end(), std::make_pair(row, col)) != alarms.end();
}

void Maze::removeAlarm(Coordinates pos) {
    auto it = std::find(alarms.begin(), alarms.end(), pos);
    if(it != alarms.end()) {
        *it = alarms.back();
        alarms.pop_back();
    }
}

int Maze::getAlarmCount() const {
    return alarms.size();
}

Coordinates Maze::getAlarm(int index) {
    if(index >= 0 && index < getAlarmCount()){
        return alarms[index];
    }
    return std::make_pair(-1, -1);
}









