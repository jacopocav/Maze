//
// Created by Admin on 19/05/2016.
//

#include "MazeGenerator.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>


Maze* MazeGenerator::generateMaze(unsigned height, unsigned width) {
    auto C = std::vector<coordinates>();

    vector<Direction> directions = {N, S, E, W};

    Maze *maze = new Maze(height, width);

    C.push_back(coordinates(1, 1));

    int seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine rnd(seed);


    while (!C.empty()) {
        std::shuffle(directions.begin(), directions.end(), rnd);
        int index = C.size() - 1;
        auto cell = C.at(static_cast<unsigned>(index));
        maze->set(cell, true);
        coordinates newCell;

        for (int i = 0; i < directions.size(); ++i) {
            newCell = cell;
            switch (directions[i]) {
                case N:
                    if (newCell.first < 2) continue;
                    newCell.first -= 2;
                    break;
                case S:
                    if (newCell.first > maze->getHeight() - 3) continue;
                    newCell.first += 2;
                    break;
                case E:
                    if (newCell.second > maze->getWidth() - 3) continue;
                    newCell.second += 2;
                    break;
                case W:
                    if (newCell.second < 2) continue;
                    newCell.second -= 2;
                    break;
            }
            if (newCell != cell && !maze->get(newCell)) {
                C.push_back(newCell);
                coordinates middleCell((cell.first + newCell.first) / 2,
                                                         (cell.second + newCell.second) / 2);
                maze->set(middleCell, true);
                maze->set(newCell, true);

                index = -1;
                break;
            }
        }
        if (index >= 0 && index < C.size()) {
            C.erase(C.begin() + index);
        }
    }
    return maze;
}



