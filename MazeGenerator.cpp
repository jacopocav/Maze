//
// Created by Admin on 19/05/2016.
//

#include "MazeGenerator.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

int seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine rnd(seed);

Maze *MazeGenerator::generateMaze(unsigned height, unsigned width) {
    auto C = std::vector<Coordinates>();

    vector<Direction> directions = {N, S, E, W};

    Maze *maze = new Maze(height, width);

    C.push_back(Coordinates(1, 1));


    while (!C.empty()) {
        std::shuffle(directions.begin(), directions.end(), rnd);
        int index = C.size() - 1;
        Coordinates cell = C.at(static_cast<unsigned>(index));
        maze->set(cell, true);
        Coordinates newCell;

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
                Coordinates middleCell((cell.first + newCell.first) / 2,
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

void MazeGenerator::addAlarmsToMaze(Maze *maze, int alarmCount) {
    for (int i = 0; i < alarmCount; ++i) {
        int x = 0, y = 0;
        bool ok = false;
        while (!ok) {
            x = 1 + rnd() % (maze->getHeight() - 2);
            y = 1 + rnd() % (maze->getHeight() - 2);
            if(maze->get(x, y) && !maze->isAlarm(static_cast<unsigned>(x), static_cast<unsigned>(y))){
                if(maze->getAlarmCount() == 0) ok = true;
                else {
                    for(int k = 0; k < maze->getAlarmCount(); ++k){
                        Coordinates alm = maze->getAlarm(k);
                        if(abs(x - alm.first) > 0.1 * maze->getHeight() && abs(y - alm.second) > 0.1 * maze->getWidth())
                            ok = true;
                        // Il percorso tra ogni allarme dev'essere lungo almeno il 5% del numero di celle totali
                        /*if(maze->solve(x, y, alm.first, alm.second) > (0.05 * maze->getHeight() * maze->getWidth())){
                            ok = true;
                        }*/
                    }
                }
            }
        }

        maze->setAlarm(std::make_pair(x, y));
    }
}



