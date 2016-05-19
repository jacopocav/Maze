//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <vector>

using std::vector;

class Maze {
private:
    vector<vector<bool>> maze;
    int height, width;
public:
    Maze(unsigned height, unsigned width);

    int getHeight() const;

    int getWidth() const;

    bool operator()(int row, int col) const;

    bool operator()(std::pair<unsigned, unsigned> coord) const;

    void setCell(int row, int col, bool val);

    void setCell(std::pair<unsigned, unsigned> coord, bool val);
};
