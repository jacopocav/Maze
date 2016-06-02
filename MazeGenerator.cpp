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
std::uniform_real_distribution<float> distribution(0.0, 1.0);

Maze *MazeGenerator::generateMaze(unsigned height, unsigned width) {
    auto activeCells = std::vector<Coordinates>();

    vector<Direction> directions = {N, S, E, W};

    Maze *maze = new Maze(height, width);

    activeCells.push_back(Coordinates(1, 1));

    const float randChance = 0.2f; // Probabilità di scegliere una cella a caso da activeCells invece che la più nuova
    while (!activeCells.empty()) {
        std::shuffle(directions.begin(), directions.end(), rnd);
        float random = distribution(rnd);
        int nextIndex;
        if(random < randChance){
            nextIndex = rnd() % (activeCells.size() - 1);
        } else {
            nextIndex = activeCells.size() - 1;
        }


        Coordinates cell = activeCells.at(static_cast<unsigned>(nextIndex));
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
                activeCells.push_back(newCell);
                Coordinates middleCell((cell.first + newCell.first) / 2,
                                       (cell.second + newCell.second) / 2);
                maze->set(middleCell, true);
                maze->set(newCell, true);

                nextIndex = -1;
                break;
            }
        }
        if (nextIndex >= 0 && nextIndex < activeCells.size()) {
            activeCells.erase(activeCells.begin() + nextIndex);
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
            if((x != 1 || y != 1) && maze->get(x, y) && !maze->isAlarm(static_cast<unsigned>(x), static_cast<unsigned>(y))){
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



