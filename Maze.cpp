//
// Created by Admin on 19/05/2016.
//

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

Maze::Maze(unsigned height, unsigned width) : start(1,1), end(height - 2, width - 2) {
    if(height % 2 == 0) height++;
    if(width % 2 == 0) width++;

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

int Maze::solve() {
    correctPathLength = 0;
    recursiveSolve(start.first, start.second);
    // Will leave you with a boolean array (correctPath)
    // with the path indicated by true values.
    // If b is false, there is no solution to the maze
    return correctPathLength;
}

bool Maze::recursiveSolve(int x, int y) {
    if (x == end.first && y == end.second) return true; // If you reached the end
    if (!maze[x][y] || wasHere[x][y]) return false;
    // If you are on a wall or already were here
    wasHere[x][y] = true;
    if (x != 0) // Checks if not on left edge
    if (recursiveSolve(x-1, y)) { // Recalls method one to the left
        correctPathLength++; // Sets that path value to true;
        return true;
    }
    if (x != maze.size() - 1) // Checks if not on right edge
    if (recursiveSolve(x+1, y)) { // Recalls method one to the right
        correctPathLength++;
        return true;
    }
    if (y != 0)  // Checks if not on top edge
    if (recursiveSolve(x, y-1)) { // Recalls method one up
        correctPathLength++;
        return true;
    }
    if (y != maze[0].size() - 1) // Checks if not on bottom edge
    if (recursiveSolve(x, y+1)) { // Recalls method one down
        correctPathLength++;
        return true;
    }
    return false;
}









