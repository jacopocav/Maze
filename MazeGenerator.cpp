//
// Created by Admin on 19/05/2016.
//

#include "MazeGenerator.h"
#include "Settings.h"
#include <ctime>
#include <algorithm>
#include <chrono>

int seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine rnd(seed);
std::uniform_real_distribution<float> distribution(0.0, 1.0);
bool braided = Settings::getInstance()["DEAD_ENDS"] == 0;
const float randomness = static_cast<float>(Settings::getInstance()["MAZE_RANDOMNESS"]) / 100;

Maze *MazeGenerator::generateMaze(unsigned height, unsigned width) {
    auto activeCells = std::vector<Coordinates>();

    vector<Direction> directions = {N, S, E, W};

    Maze *maze = new Maze(height, width);

    activeCells.push_back(Coordinates(1, 1));

    while (!activeCells.empty()) {
        std::shuffle(directions.begin(), directions.end(), rnd);
        float random = distribution(rnd);
        int index;

        // activeCells deve avere più di un elemento, altrimenti il modulo sarebbe con 0, il che non è permesso
        if (random < randomness && activeCells.size() > 1) {
            index = rnd() % (activeCells.size() - 1);
        } else {
            index = activeCells.size() - 1;
        }


        Coordinates cell = activeCells.at(static_cast<unsigned>(index));
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

                index = -1;
                break;
            }
        }
        if (index >= 0 && index < activeCells.size()) {
            activeCells.erase(activeCells.begin() + index);
        }
    }

    if (braided) {
        for (int x = 1; x < maze->getHeight(); x += 2) {
            for (int y = 1; y < maze->getWidth(); y += 2) {
                cullDeadEnd(maze, std::make_pair(x, y));
            }
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
            if ((x != 1 || y != 1) && maze->get(x, y) &&
                !maze->isAlarm(static_cast<unsigned>(x), static_cast<unsigned>(y))) {
                if (maze->getAlarmCount() == 0) ok = true;
                else {
                    for (int k = 0; k < maze->getAlarmCount(); ++k) {
                        Coordinates alm = maze->getAlarm(k);
                        if (abs(x - alm.first) > 0.1 * maze->getHeight() &&
                            abs(y - alm.second) > 0.1 * maze->getWidth())
                            ok = true;
                    }
                }
            }
        }

        maze->setAlarm(std::make_pair(x, y));
    }
}


void MazeGenerator::cullDeadEnd(Maze *maze, Coordinates cell) {
    int links = 0;
    Coordinates neighbor = cell;
    vector<Coordinates> candidates;
    if (!maze->get(cell)) return;

    if (neighbor.first > 2) {// Controllo Nord
        neighbor.first -= 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.first < maze->getHeight() - 2) {// Controllo Sud
        neighbor.first += 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.second > 2) {// Controllo Est
        neighbor.second -= 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.second < maze->getWidth() - 2) {// Controllo Ovest
        neighbor.second += 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    if (links == 1) {
        std::shuffle(candidates.begin(), candidates.end(), rnd);
        maze->set(candidates[0], true);
    }

}