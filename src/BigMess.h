//
// Created by Admin on 24/05/2016.
//

#pragma once


#include <GL/glut.h>
#include "game/MazeGenerator.h"
#include "gfx/MazeCamera.h"

class BigMess {
public:
    static void Init();

    static void Display();

    static void Reshape(int w, int h);

    static void Keyboard(unsigned char key, int x, int y);

    static void KeyboardUp(unsigned char key, int x, int y);

    static void KeyboardSpecial(int key, int x, int y);

    static void KeyboardSpecialUp(int key, int x, int y);

    static void MouseMotion(int x, int y);

    static void Mouse(int button, int state, int x, int y);

    static void Timer(int value);

    static void Idle();

private:
    static void InitGame();
    static void UpdateGameStatus(int timeDiff);

    static int GetTimeLimit(int startX, int startY);

    static void GameOver(bool win);

    static void Cleanup();

    static int currTime_;
    static int timeLimit_;

    static game::Maze *maze_;
    static gfx::MazeCamera camera_;
    static bool key_[256];
    static bool specialKey_[4];
    static bool fpsMode_;
    static int viewportWidth_;
    static int viewportHeight_;
    static bool mouseLeftDown_;
    static bool mouseRightDown_;
    static bool justWarped_;

    static const float lightPos_[4];

    // Costanti che definiscono la velocità di movimento/rotazione
    static const float translationSpeed_;
    static const float rotationSpeed_;
};
