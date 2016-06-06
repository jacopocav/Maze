//
// Created by Admin on 24/05/2016.
//

#pragma once

#include <map>

#include <GL/glut.h>

#include "game/MazeGenerator.h"
#include "audio/Source.h"
#include "audio/Manager.h"

class GlutCallbacks {
    friend class InputCallbacks;
private:
    static void initGame();

    static void updateGameStatus(int timeDiff);

    static void gameOver(bool win);

    static void cleanup();

    static int remainingTime_;
    static audio::Manager audioManager_;
    static game::Maze *maze_;
    static const float lightPos_[4];
    // Costanti che definiscono la velocità di movimento/rotazione
    static const unsigned MAZE_HEIGHT, MAZE_WIDTH;
    static const int ALARM_COUNT;

public:
    static void init();

    static void display();

    static void reshape(int width, int height);

    static void idle();
};
