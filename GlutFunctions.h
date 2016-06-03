//
// Created by Admin on 24/05/2016.
//

#pragma once


#include <GL/glut.h>
#include "MazeGenerator.h"
#include "MazeCamera.h"

class GlutFunctions {
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

    static int currTime;
    static int timeLimit;

    static Maze *m_maze;
    static MazeCamera g_camera;
    static bool g_key[256];
    static bool g_special_key[4];
    static bool g_fps_mode;
    static int g_viewport_width;
    static int g_viewport_height;
    static bool g_mouse_left_down;
    static bool g_mouse_right_down;
    static bool just_warped;

    static const float light_pos[4];

    // Costanti che definiscono la velocità di movimento/rotazione
    static const float g_translation_speed;
    static const float g_rotation_speed;
};
