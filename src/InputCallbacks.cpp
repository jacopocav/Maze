//
// Created by Admin on 05/06/2016.
//

#include "GlutCallbacks.h"
#include "InputCallbacks.h"
#include "game/Time.h"
#include "game/Settings.h"

const float InputCallbacks::TRANSLATION_SPEED = 0.0008;
const float InputCallbacks::ROTATION_SPEED = constants::PI / 180 * 0.15f;

bool InputCallbacks::key_[256];
bool InputCallbacks::specialKey_[4];
bool InputCallbacks::movement_ = false;
bool InputCallbacks::mouseLeftDown_ = false;
bool InputCallbacks::mouseRightDown_ = false;

gfx::MazeCamera InputCallbacks::camera_(nullptr);

int InputCallbacks::viewportWidth_ = 0;
int InputCallbacks::viewportHeight_ = 0;
int InputCallbacks::currTime_;

void InputCallbacks::keyboard(unsigned char key, int, int) {
    if (key == 27) { // ESC chiude il gioco
        GlutCallbacks::cleanup();
        exit(0);
    }

    if (key == 'r' || key == 'R') { // Con R si chiude la partita corrente e se ne inizia una nuova
        GlutCallbacks::gameOver(false);
    }

    if (key == ' ') { // SPAZIO permette di (dis)attivare la pausa e (dis)abilitare il movimento
        movement_ = !movement_;

        if (movement_) {
            GlutCallbacks::audioManager_.playAll();
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(viewportWidth_ / 2, viewportHeight_ / 2);
        }
        else {
            GlutCallbacks::audioManager_.pauseAll();
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }


    key_[key] = true;
}

void InputCallbacks::keyboardUp(unsigned char key, int, int) {
    key_[key] = false;
}

void InputCallbacks::keyboardSpecial(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            specialKey_[0] = true;
            break;
        case GLUT_KEY_DOWN:
            specialKey_[1] = true;
            break;
        case GLUT_KEY_LEFT:
            specialKey_[2] = true;
            break;
        case GLUT_KEY_RIGHT:
            specialKey_[3] = true;
            break;
        default:
            return;
    }
}

void InputCallbacks::keyboardSpecialUp(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            specialKey_[0] = false;
            break;
        case GLUT_KEY_DOWN:
            specialKey_[1] = false;
            break;
        case GLUT_KEY_LEFT:
            specialKey_[2] = false;
            break;
        case GLUT_KEY_RIGHT:
            specialKey_[3] = false;
            break;
        default:
            return;
    }
}

void InputCallbacks::timer(int) {
    int newTime = game::Time::getCurrentTimeMillis();
    int timeDiff = newTime - currTime_;
    currTime_ = newTime;
    if (movement_) {
        if (key_['w'] || key_['W']) {
            InputCallbacks::camera_.move(TRANSLATION_SPEED * timeDiff);
        }
        else if (key_['s'] || key_['S']) {
            InputCallbacks::camera_.move(-TRANSLATION_SPEED * timeDiff);
        }
        if (key_['a'] || key_['A']) {
            InputCallbacks::camera_.strafe(TRANSLATION_SPEED * timeDiff);
        }
        else if (key_['d'] || key_['D']) {
            InputCallbacks::camera_.strafe(-TRANSLATION_SPEED * timeDiff);
        }

        // I Comandi di "volo" sono eseguiti solo se abilitati da impostazioni
        if (game::Settings::getInstance()["ENABLE_FLIGHT"] != 0) {
            if (mouseLeftDown_) {
                InputCallbacks::camera_.fly(-2 * TRANSLATION_SPEED * timeDiff);
            }
            else if (mouseRightDown_) {
                InputCallbacks::camera_.fly(2 * TRANSLATION_SPEED * timeDiff);
            }

            if (specialKey_[0]) {
                InputCallbacks::camera_.fly(2 * TRANSLATION_SPEED * timeDiff);
            }
            else if (specialKey_[1]) {
                InputCallbacks::camera_.fly(-2 * TRANSLATION_SPEED * timeDiff);
            }
        }
        if (specialKey_[2]) {
            InputCallbacks::camera_.rotateYaw(-ROTATION_SPEED * timeDiff);
        }
        else if (specialKey_[3]) {
            InputCallbacks::camera_.rotateYaw(ROTATION_SPEED * timeDiff);
        }

        GlutCallbacks::updateGameStatus(timeDiff);
    }

    glutTimerFunc(16, timer, 0);
}

void InputCallbacks::mouse(int button, int state, int, int) {
    if (state == GLUT_DOWN) { // Tasto premuto
        if (button == GLUT_LEFT_BUTTON) {
            mouseLeftDown_ = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseRightDown_ = true;
        }
    }
    else if (state == GLUT_UP) { // Tasto rilasciato
        if (button == GLUT_LEFT_BUTTON) {
            mouseLeftDown_ = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseRightDown_ = false;
        }
    }
}

void InputCallbacks::mouseMotion(int x, int y) {
    // Poiché glutWarpPointer provoca una chiamata ricorsiva a mouseMotion,
    // justWarped serve ad evitare una catena infinita di invocazioni (warp->motion->warp->motion...).
    static bool justWarped = false;

    if (movement_) {
        if (justWarped) {
            justWarped = false;
            return;
        }
        int dx = x - viewportWidth_ / 2;
        int dy = y - viewportHeight_ / 2;

        if (dx) {
            InputCallbacks::camera_.rotateYaw(ROTATION_SPEED * dx);
        }

        if (dy) {
            InputCallbacks::camera_.rotatePitch(ROTATION_SPEED * dy);
        }

        glutWarpPointer(viewportWidth_ / 2, viewportHeight_ / 2); // Riporta il cursore al centro della finestra

        justWarped = true;
    }
}