//
// Created by Admin on 24/05/2016.
//

#pragma once


#include "MazeGenerator.h"
#include "MazeCamera.h"

class GlutUtils {
public:
    static void DrawFloor(float x1, float x2, float y1, float z1, float z2, bool winFloor = false);

    static void DrawCube(float x1, float x2, float y1, float y2, float z1, float z2);

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

    static void SetFPSMode(bool mode);

private:
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

// Movement settings
    static const float g_translation_speed;
    static const float g_rotation_speed;
    static const float g_keyboard_rotation_multiplier;
};
