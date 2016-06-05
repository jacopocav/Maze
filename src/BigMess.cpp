//
// Created by Admin on 24/05/2016.
//
#include <sstream>
#include <iomanip>
#include <cmath>
#include <GL/freeglut.h>
#include "BigMess.h"
#include "gfx/Textures.h"
#include "gfx/Drawing.h"
#include "game/Settings.h"
#include "audio/Buffer.h"
#include "audio/Manager.h"
#include "audio/Listener.h"

game::Maze *BigMess::maze_;
gfx::MazeCamera BigMess::camera_(nullptr);
int BigMess::currTime_;
int BigMess::timeLimit_;
bool BigMess::key_[256] = {};
bool BigMess::specialKey_[4] = {};
bool BigMess::fpsMode_ = false;
int BigMess::viewportWidth_ = 0;
int BigMess::viewportHeight_ = 0;
bool BigMess::mouseLeftDown_ = false;
bool BigMess::mouseRightDown_ = false;

bool BigMess::justWarped_ = false;

std::vector<audio::Buffer> bufs;
std::map<game::Coordinates, audio::Source> alms;

const float BigMess::lightPos_[4] = {0.0f, 0.0f, 0.0f, 1.0f};

const float BigMess::translationSpeed_ = 0.0008;
const float BigMess::rotationSpeed_ = gfx::Camera::PI / 180 * 0.15f;

unsigned mazeX = static_cast<unsigned>(game::Settings::getInstance()["MAZE_SIZE_X"]),
        mazeY = static_cast<unsigned>(game::Settings::getInstance()["MAZE_SIZE_Y"]);
int alarmCount = game::Settings::getInstance()["ALARM_COUNT"];

void BigMess::InitGame() {
    if (maze_ != nullptr) delete maze_;
    maze_ = game::MazeGenerator::generateMaze(mazeX, mazeY);
    game::MazeGenerator::addAlarmsToMaze(maze_, alarmCount);

    alms = audio::Manager::bindSourcesToAlarms(maze_, bufs);

    camera_.setMaze(maze_);
    camera_.setPos(0, 0, 0);
    camera_.setPitch(0);
    camera_.setYaw(0);

    timeLimit_ = GetTimeLimit(1, 1);
    currTime_ = glutGet(GLUT_ELAPSED_TIME);
}

int manhattanDistance(const game::Coordinates &pos1, const game::Coordinates &pos2) {
    return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

int BigMess::GetTimeLimit(int startX, int startY) {
    if (maze_->getAlarmCount() == 0) return 0;
    bool deadEnds = game::Settings::getInstance()["DEAD_ENDS"] == 1;

    int totalSteps = 0;
    for (int i = 0; i < maze_->getAlarmCount(); ++i) {
        game::Coordinates alm = maze_->getAlarm(i);

        if(deadEnds){
            totalSteps += maze_->pathLength(startX, startY, alm.first, alm.second);
        } else {
            totalSteps += manhattanDistance(std::make_pair(startX, startY), alm);
        }
    }
    int time = (totalSteps / maze_->getAlarmCount()) * (deadEnds ? 1000 : 2000);
    return time;
}


void BigMess::Init() {
    int AAFactor = game::Settings::getInstance()["MULTISAMPLING"];
    if(AAFactor % 2 != 0){
        AAFactor -= AAFactor % 2;
    }
    if(AAFactor > 0){
        glutSetOption(GLUT_MULTISAMPLE, 4);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glEnable(GLUT_MULTISAMPLE);
    } else {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    }
    glutInitWindowSize(1024, 768);
    glutCreateWindow("SPAZIO per attivare/disattivare controlli FPS");

    glutIgnoreKeyRepeat(1);
    glClearColor(0, 0, 0, 1.0f);

    // Assegnazione callback
    glutDisplayFunc(BigMess::Display);
    glutIdleFunc(BigMess::Idle);
    glutReshapeFunc(BigMess::Reshape);
    glutMouseFunc(BigMess::Mouse);
    glutMotionFunc(BigMess::MouseMotion);
    glutPassiveMotionFunc(BigMess::MouseMotion);
    glutKeyboardFunc(BigMess::Keyboard);
    glutKeyboardUpFunc(BigMess::KeyboardUp);
    glutSpecialFunc(BigMess::KeyboardSpecial);
    glutSpecialUpFunc(BigMess::KeyboardSpecialUp);
    glutTimerFunc(16, BigMess::Timer, 0);

    // Configurazione camera
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    GLfloat black[4] = {0, 0, 0, 1};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

    float ambient_light[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuse_light[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float specular_light[4] = {1, 1, 1, 1};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.5f);

    float material[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_SPECULAR, material);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    glMateriali(GL_FRONT, GL_SHININESS, 32);

    glEnable(GL_TEXTURE_2D);

    gfx::Textures::initTextures(3);
    gfx::Textures::readFromBMP("res/texture/alt_floor.bmp", 1, "floor");
    gfx::Textures::readFromBMP("res/texture/lux_wall.bmp", 0, "wall");
    gfx::Textures::readFromBMP("res/texture/lux_ceil.bmp", 2, "ceil");

    bufs = audio::Manager::init();
    InitGame();

    glutMainLoop();
}

std::vector<float> crossVector(const std::vector<float> &a, const std::vector<float> &b) {
    std::vector<float> result(a.size());
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}


void BigMess::Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer_ and the depth buffer_
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera_.refresh();

    float cpos[3] = {0, 0, 0};
    camera_.getPos(cpos[0], cpos[1], cpos[2]);
    audio::Listener::setPosition(cpos[0], cpos[1], cpos[2]);

    std::vector<float> at = {0, 0, 0};
    camera_.getDirectionVector(at[0], at[1], at[2]);
    auto right = crossVector(at, {0, 1, 0});
    auto up = crossVector(right, at);
    audio::Listener::setOrientation(at[0], at[1], at[2], up[0], up[1], up[2]);

    glTranslatef(-0.6f, 0, 0.6);

    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos_);
    glPopMatrix();

    game::Coordinates pos = camera_.getMazeCoordinates();

    gfx::Drawing::drawMaze(maze_, pos.first, pos.second);

    glutSwapBuffers();
}


void BigMess::Reshape(int w, int h) {
    viewportWidth_ = w;
    viewportHeight_ = h;

    glViewport(0, 0, w, h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //set the perspective (angle of sight, width, height, ,depth)
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.001, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void BigMess::Keyboard(unsigned char key, int, int) {
    if (key == 27) {
        Cleanup();
        exit(0);
    }

    if (key == 'r' || key == 'R') {
        GameOver(false);
    }

    if (key == ' ') {
        fpsMode_ = !fpsMode_;

        if (fpsMode_) {
            for(auto it = alms.begin(); it != alms.end(); ++it){
                it->second.play();
            }
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(viewportWidth_ / 2, viewportHeight_ / 2);
        }
        else {
            for(auto it = alms.begin(); it != alms.end(); ++it){
                it->second.pause();
            }
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }


    key_[key] = true;
}

void BigMess::KeyboardUp(unsigned char key, int, int) {
    key_[key] = false;
}

void BigMess::KeyboardSpecial(int key, int, int) {
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

void BigMess::KeyboardSpecialUp(int key, int, int) {
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


void BigMess::Timer(int) {
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    int timeDiff = newTime - currTime_;
    currTime_ = newTime;
    if (fpsMode_) {
        if (key_['w'] || key_['W']) {
            camera_.move(translationSpeed_ * timeDiff);
        }
        else if (key_['s'] || key_['S']) {
            camera_.move(-translationSpeed_ * timeDiff);
        }
        if (key_['a'] || key_['A']) {
            camera_.strafe(translationSpeed_ * timeDiff);
        }
        else if (key_['d'] || key_['D']) {
            camera_.strafe(-translationSpeed_ * timeDiff);
        }

        if(game::Settings::getInstance()["ENABLE_FLIGHT"] != 0) {
            if (mouseLeftDown_) {
                camera_.fly(-2 * translationSpeed_ * timeDiff);
            }
            else if (mouseRightDown_) {
                camera_.fly(2 * translationSpeed_ * timeDiff);
            }
        }
        if (specialKey_[0]) {
            camera_.rotatePitch(-rotationSpeed_ * timeDiff);
        }
        else if (specialKey_[1]) {
            camera_.rotatePitch(rotationSpeed_ * timeDiff);
        }
        if (specialKey_[2]) {
            camera_.rotateYaw(-rotationSpeed_ * timeDiff);
        }
        else if (specialKey_[3]) {
            camera_.rotateYaw(rotationSpeed_ * timeDiff);
        }

        UpdateGameStatus(timeDiff);
    }

    glutTimerFunc(16, Timer, 0);
}

void BigMess::UpdateGameStatus(int timeDiff) {
    game::Coordinates pos = camera_.getMazeCoordinates();

    timeLimit_ -= timeDiff;

    std::stringstream windowTitle;

    if (maze_->isAlarm(pos)) {
        maze_->removeAlarm(pos);
        alms.at(pos).release();
        alms.erase(pos);
        if (maze_->getAlarmCount() > 0) {
            timeLimit_ = std::max(timeLimit_, GetTimeLimit(pos.first, pos.second));
        }
        else GameOver(true);
    } else if (timeLimit_ <= 0) {
        GameOver(false);
    } else {
        windowTitle << "Tempo: ";
        windowTitle << std::setfill('0') << std::setw(2) << timeLimit_ / 60000;
        windowTitle << ":";
        windowTitle << std::setfill('0') << std::setw(2) << (timeLimit_ / 1000) % 60;

        windowTitle << "  Posizione: (";
        windowTitle << pos.first << ", ";
        windowTitle << pos.second << ")";

        /*float camPos[3] = {0, 0, 0};
        camera_.getPos(camPos[0], camPos[1], camPos[2]);
        windowTitle << " [" << camPos[0] << ", " << camPos[1] << ", " << camPos[2] << "]";*/

        windowTitle << "  Allarmi rimanenti: " << maze_->getAlarmCount();

        glutSetWindowTitle(windowTitle.str().c_str());
    }
}

void BigMess::GameOver(bool win) {
    std::stringstream windowTitle;
    if (!win) windowTitle << "Tempo Scaduto! Hai perso!";
    else windowTitle << "Hai vinto!!!";
    windowTitle << " Premi SPAZIO per cominciare una nuova partita.";

    for(auto it = alms.begin(); it != alms.end(); ++it){
        it->second.release();
    }

    fpsMode_ = false;
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    glutSetWindowTitle(windowTitle.str().c_str());
    InitGame();
}

void BigMess::Idle() {
    Display();
}

void BigMess::Mouse(int button, int state, int, int) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            mouseLeftDown_ = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseRightDown_ = true;
        }
    }
    else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            mouseLeftDown_ = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseRightDown_ = false;
        }
    }
}

void BigMess::MouseMotion(int x, int y) {
    if (justWarped_) {
        justWarped_ = false;
        return;
    }

    if (fpsMode_) {
        int dx = x - viewportWidth_ / 2;
        int dy = y - viewportHeight_ / 2;

        if (dx) {
            camera_.rotateYaw(rotationSpeed_ * dx);
        }

        if (dy) {
            camera_.rotatePitch(rotationSpeed_ * dy);
        }

        glutWarpPointer(viewportWidth_ / 2, viewportHeight_ / 2);

        justWarped_ = true;
    }
}

void BigMess::Cleanup() {
    delete maze_;
    gfx::Textures::resetTextures();

    for(auto it = alms.begin(); it != alms.end(); ++it){
        it->second.release();
    }

    for(auto it = bufs.begin(); it != bufs.end(); ++it){
        it->release();
    }
}