//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <vector>

using std::vector;

// Viene utilizzato questo tipo per indicare le coordinate di una cella nel labirinto
typedef std::pair<unsigned, unsigned> coordinates;

class Maze {
private:
    vector<vector<bool>> maze;
public:
    Maze(unsigned height, unsigned width);

    int getHeight() const;

    int getWidth() const;

    // Ritornano il valore di una cella
    bool get(int row, int col) const;
    bool get(coordinates coord) const;

    // Impostano il valore di una cella
    void set(int row, int col, bool val);
    void set(coordinates coord, bool val);
};
