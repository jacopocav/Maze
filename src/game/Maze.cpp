//
// Created by Admin on 19/05/2016.
//

#include <cstdlib>
#include <algorithm>
#include "Maze.h"

int game::Maze::getHeight() const {
    return maze_.size();
}

int game::Maze::getWidth() const {
    return maze_[0].size();
}

bool game::Maze::get(int row, int col) const {
    return maze_[row][col];
}

game::Maze::Maze(unsigned height, unsigned width) : alarms_(), isBraided_(false) {
    if (height % 2 == 0) height++;
    if (width % 2 == 0) width++;

    maze_.resize(height);
    for (auto i = 0; i < height; ++i) {
        maze_[i].assign(width, false); // Tutti muri
    }
    wasHere_.resize(height);
}

bool game::Maze::get(game::Coordinates coord) const {
    return get(coord.first, coord.second);
}

int correctPathLength = 0; // Lunghezza del percorso calcolato in pathLength

int game::Maze::pathLength(const Coordinates &start, const Coordinates &end) {
    correctPathLength = 0;
    for(int i = 0; i < wasHere_.size(); ++i){
        wasHere_[i].assign(maze_[i].size(), false);
    }
    recursiveSolve(start.first, start.second, end.first, end.second);

    return correctPathLength;
}

bool game::Maze::recursiveSolve(int x, int y, int endX, int endY) {
    if (x == endX && y == endY) return true; // Raggiunta la fine
    if (!maze_[x][y] || wasHere_[x][y]) return false; // La posizione corrente è un muro o è già stata percorsa

    wasHere_[x][y] = true;
    if (x != 0 && recursiveSolve(x - 1, y, endX, endY)) { // Se non siamo sul bordo sx, prova ad andare a sx
        correctPathLength++;
        return true;
    }
    if (x != maze_.size() - 1 && recursiveSolve(x + 1, y, endX, endY)) { // Destra
        correctPathLength++;
        return true;
    }
    if (y != 0 && recursiveSolve(x, y - 1, endX, endY)) { // Su
        correctPathLength++;
        return true;
    }
    if (y != maze_[0].size() - 1 && recursiveSolve(x, y + 1, endX, endY)) { // Giù
        correctPathLength++;
        return true;
    }
    return false;
}

bool game::Maze::isAlarm(const Coordinates &pos) const {
    return std::find(alarms_.begin(), alarms_.end(), pos) != alarms_.end();
}

bool game::Maze::isAlarm(unsigned row, unsigned col) const {
    return std::find(alarms_.begin(), alarms_.end(), std::make_pair(row, col)) != alarms_.end();
}

void game::Maze::removeAlarm(const Coordinates &pos) {
    auto it = std::find(alarms_.begin(), alarms_.end(), pos);
    if(it != alarms_.end()) {
        *it = alarms_.back();
        alarms_.pop_back();
    }
}

int game::Maze::getAlarmCount() const {
    return alarms_.size();
}

game::Coordinates game::Maze::getAlarm(int index) const {
    if(index >= 0 && index < getAlarmCount()){
        return alarms_[index];
    }
    return std::make_pair(-1, -1);
}

bool game::Maze::isBraided() const {
    return isBraided_;
}








