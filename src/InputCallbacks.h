//
// Created by Admin on 05/06/2016.
//

#pragma once


#include "gfx/MazeCamera.h"

class InputCallbacks {
    friend class GlutCallbacks;
private:
    static gfx::MazeCamera camera_;
    static int viewportWidth_;
    static int viewportHeight_;
    static bool key_[256];
    static bool specialKey_[4];
    static bool fpsMode_;
    static bool mouseLeftDown_;
    static bool mouseRightDown_;
    static bool justWarped_;
    static const float TRANSLATION_SPEED;
    static const float ROTATION_SPEED;
    static int currTime_;
public:
    static void keyboard(unsigned char key, int x, int y);

    static void keyboardUp(unsigned char key, int x, int y);

    static void keyboardSpecial(int key, int x, int y);

    static void keyboardSpecialUp(int key, int x, int y);

    static void timer(int value);

    static void mouse(int button, int state, int x, int y);

    static void mouseMotion(int x, int y);
};


