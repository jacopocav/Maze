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

Maze::Maze(unsigned height, unsigned width) {
    if(height % 2 == 0) height++;
    if(width % 2 == 0) width++;

    maze.resize(height);
    for (auto i = 0; i < height; ++i) {
        maze[i].assign(width, false);
    }
}

bool Maze::get(coordinates coord) const {
    return get(coord.first, coord.second);
}

void Maze::set(coordinates coord, bool val) {
    set(coord.first, coord.second, val);
}

void Maze::set(int row, int col, bool val) {
    maze[row][col] = val;
}









