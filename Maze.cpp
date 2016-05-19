//
// Created by Admin on 19/05/2016.
//

#include "Maze.h"

int Maze::getHeight() const {
    return height;
}

int Maze::getWidth() const {
    return width;
}

bool Maze::operator()(int row, int col) const {
    return maze[row][col];
}

Maze::Maze(unsigned height, unsigned width) {
    this->width = width;
    this->height = height;
    maze.resize(height);
    for (auto i = 0; i < height; ++i) {
        maze[i].assign(width, false);
    }
}

bool Maze::operator()(std::pair<unsigned, unsigned> coord) const {
    operator()(coord.first, coord.second);
}

void Maze::setCell(std::pair<unsigned, unsigned> coord, bool val) {
    setCell(coord.first, coord.second, val);
}

void Maze::setCell(int row, int col, bool val) {
    maze[row][col] = val;
}









