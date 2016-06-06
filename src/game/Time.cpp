//
// Created by Admin on 05/06/2016.
//

#include <cstdlib>
#include <chrono>
#include "Time.h"

int game::Time::manhattanDistance(game::Coordinates pos1, game::Coordinates pos2) {
    return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

int game::Time::getTimeLimit(Maze *maze, game::Coordinates currentPos) {
    if(maze->getAlarmCount() == 0) return 0;

    int totalSteps = 0;
    for (int i = 0; i < maze->getAlarmCount(); ++i) {
        game::Coordinates alarm = maze->getAlarm(i);

        if(maze->isBraided()){
            totalSteps += manhattanDistance(currentPos, alarm);
        } else {
            totalSteps += maze->pathLength(currentPos, alarm);
        }
    }
    int time = (totalSteps / maze->getAlarmCount()) * (maze->isBraided() ? 2000 : 1000);
    return time;
}



int game::Time::getCurrentTimeMillis() {
    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
}