//
// Created by Admin on 24/05/2016.
//
#include <sstream>
#include <iomanip>
#include <cmath>
#include <GL/freeglut.h>
#include "GlutFunctions.h"
#include "TextureFunctions.h"
#include "DrawingFunctions.h"
#include "AudioFunctions.h"
#include "Settings.h"

Maze *GlutFunctions::m_maze;
MazeCamera GlutFunctions::g_camera(nullptr);
int GlutFunctions::currTime;
int GlutFunctions::timeLimit;
bool GlutFunctions::g_key[256] = {};
bool GlutFunctions::g_special_key[4] = {};
bool GlutFunctions::g_fps_mode = false;
int GlutFunctions::g_viewport_width = 0;
int GlutFunctions::g_viewport_height = 0;
bool GlutFunctions::g_mouse_left_down = false;
bool GlutFunctions::g_mouse_right_down = false;

bool GlutFunctions::just_warped = false;

const float GlutFunctions::light_pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};

const float GlutFunctions::g_translation_speed = 0.0008;
const float GlutFunctions::g_rotation_speed = Camera::M_PI / 180 * 0.15f;

unsigned mazeX = static_cast<unsigned>(Settings::getInstance()["MAZE_SIZE_X"]),
        mazeY = static_cast<unsigned>(Settings::getInstance()["MAZE_SIZE_Y"]);
int alarmCount = Settings::getInstance()["ALARM_COUNT"];

void GlutFunctions::InitGame() {
    if (m_maze != nullptr) delete m_maze;
    m_maze = MazeGenerator::generateMaze(mazeX, mazeY);
    MazeGenerator::addAlarmsToMaze(m_maze, alarmCount);
    AudioFunctions::InitSources(alarmCount);

    for (int i = 0; i < alarmCount; ++i) {
        std::stringstream path, name;
        path << "res/audio/alarm" << i % 5 << ".wav";
        Coordinates alm = m_maze->getAlarm(i);
        name << "alarm" << alm.first << "_" << alm.second;
        AudioFunctions::LoadSourceFromFile(path.str(), i, name.str(), true,
                                           1.0f + ((i - (i % alarmCount)) / alarmCount * 0.3f));
        AudioFunctions::SetSourcePosition(name.str(), alm.first * 0.4f - 0.4f, 0.0f, alm.second * -0.4f + 0.4f);
    }

    g_camera.SetMaze(m_maze);
    g_camera.SetPos(0, 0, 0);
    g_camera.SetPitch(0);
    g_camera.SetYaw(0);

    timeLimit = GetTimeLimit(1, 1);
    currTime = glutGet(GLUT_ELAPSED_TIME);
}

int manhattanDistance(const Coordinates &pos1, const Coordinates &pos2) {
    return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

int GlutFunctions::GetTimeLimit(int startX, int startY) {
    if (m_maze->getAlarmCount() == 0) return 0;
    bool deadEnds = Settings::getInstance()["DEAD_ENDS"] == 1;

    int totalSteps = 0;
    for (int i = 0; i < m_maze->getAlarmCount(); ++i) {
        Coordinates alm = m_maze->getAlarm(i);

        if(deadEnds){
            totalSteps += m_maze->pathLength(startX, startY, alm.first, alm.second);
        } else {
            totalSteps += manhattanDistance(std::make_pair(startX, startY), alm);
        }
    }
    int time = (totalSteps / m_maze->getAlarmCount()) * (deadEnds ? 1000 : 2000);
    return time;
}


void GlutFunctions::Init() {
    int AAFactor = Settings::getInstance()["MULTISAMPLING"];
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
    glutDisplayFunc(GlutFunctions::Display);
    glutIdleFunc(GlutFunctions::Idle);
    glutReshapeFunc(GlutFunctions::Reshape);
    glutMouseFunc(GlutFunctions::Mouse);
    glutMotionFunc(GlutFunctions::MouseMotion);
    glutPassiveMotionFunc(GlutFunctions::MouseMotion);
    glutKeyboardFunc(GlutFunctions::Keyboard);
    glutKeyboardUpFunc(GlutFunctions::KeyboardUp);
    glutSpecialFunc(GlutFunctions::KeyboardSpecial);
    glutSpecialUpFunc(GlutFunctions::KeyboardSpecialUp);
    glutTimerFunc(16, GlutFunctions::Timer, 0);

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

    TextureFunctions::InitTextures(3);
    TextureFunctions::ReadFromBMP("res/texture/alt_floor.bmp", 1, "floor");
    TextureFunctions::ReadFromBMP("res/texture/lux_wall.bmp", 0, "wall");
    TextureFunctions::ReadFromBMP("res/texture/lux_ceil.bmp", 2, "ceil");


    AudioFunctions::InitSources(0);
    InitGame();

    glutMainLoop();
}

vector<float> crossVector(const vector<float> &a, const vector<float> &b) {
    vector<float> result(a.size());
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}


void GlutFunctions::Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    g_camera.Refresh();

    float cpos[3] = {0, 0, 0};
    g_camera.GetPos(cpos[0], cpos[1], cpos[2]);
    AudioFunctions::SetListenerPosition(cpos[0], cpos[1], cpos[2]);

    vector<float> at = {0, 0, 0};
    g_camera.GetDirectionVector(at[0], at[1], at[2]);
    auto right = crossVector(at, {0, 1, 0});
    auto up = crossVector(right, at);
    AudioFunctions::SetListenerOrientation(at[0], at[1], at[2], up[0], up[1], up[2]);

    glTranslatef(-0.6f, 0, 0.6);

    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glPopMatrix();

    Coordinates pos = g_camera.getMazeCoordinates();

    DrawingFunctions::DrawMaze(m_maze, pos.first, pos.second);

    glutSwapBuffers();
}


void GlutFunctions::Reshape(int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport(0, 0, w, h); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //set the perspective (angle of sight, width, height, ,depth)
    gluPerspective(45, (GLfloat) w / (GLfloat) h, 0.001, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void GlutFunctions::Keyboard(unsigned char key, int, int) {
    if (key == 27) {
        Cleanup();
        exit(0);
    }

    if (key == 'r' || key == 'R') {
        GameOver(false);
    }

    if (key == ' ') {
        g_fps_mode = !g_fps_mode;

        if (g_fps_mode) {
            AudioFunctions::PlayAll();
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);
        }
        else {
            AudioFunctions::PauseAll();
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }


    g_key[key] = true;
}

void GlutFunctions::KeyboardUp(unsigned char key, int, int) {
    g_key[key] = false;
}

void GlutFunctions::KeyboardSpecial(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            g_special_key[0] = true;
            break;
        case GLUT_KEY_DOWN:
            g_special_key[1] = true;
            break;
        case GLUT_KEY_LEFT:
            g_special_key[2] = true;
            break;
        case GLUT_KEY_RIGHT:
            g_special_key[3] = true;
            break;
        default:
            return;
    }
}

void GlutFunctions::KeyboardSpecialUp(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            g_special_key[0] = false;
            break;
        case GLUT_KEY_DOWN:
            g_special_key[1] = false;
            break;
        case GLUT_KEY_LEFT:
            g_special_key[2] = false;
            break;
        case GLUT_KEY_RIGHT:
            g_special_key[3] = false;
            break;
        default:
            return;
    }
}


void GlutFunctions::Timer(int) {
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    int timeDiff = newTime - currTime;
    currTime = newTime;
    if (g_fps_mode) {
        if (g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed * timeDiff);
        }
        else if (g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed * timeDiff);
        }
        if (g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed * timeDiff);
        }
        else if (g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed * timeDiff);
        }

        if(Settings::getInstance()["ENABLE_FLIGHT"] != 0) {
            if (g_mouse_left_down) {
                g_camera.Fly(-2 * g_translation_speed * timeDiff);
            }
            else if (g_mouse_right_down) {
                g_camera.Fly(2 * g_translation_speed * timeDiff);
            }
        }
        if (g_special_key[0]) {
            g_camera.RotatePitch(-g_rotation_speed * timeDiff);
        }
        else if (g_special_key[1]) {
            g_camera.RotatePitch(g_rotation_speed * timeDiff);
        }
        if (g_special_key[2]) {
            g_camera.RotateYaw(-g_rotation_speed * timeDiff);
        }
        else if (g_special_key[3]) {
            g_camera.RotateYaw(g_rotation_speed * timeDiff);
        }

        UpdateGameStatus(timeDiff);
    }

    glutTimerFunc(16, Timer, 0);
}

void GlutFunctions::UpdateGameStatus(int timeDiff) {
    Coordinates pos = g_camera.getMazeCoordinates();

    timeLimit -= timeDiff;

    std::stringstream windowTitle;

    if (m_maze->isAlarm(pos)) {
        m_maze->removeAlarm(pos);
        std::stringstream name;
        name << "alarm" << pos.first << "_" << pos.second;
        AudioFunctions::RemoveSource(name.str());
        if (m_maze->getAlarmCount() > 0) {
            timeLimit = std::max(timeLimit, GetTimeLimit(pos.first, pos.second));
        }
        else GameOver(true);
    } else if (timeLimit <= 0) {
        GameOver(false);
    } else {
        windowTitle << "Tempo: ";
        windowTitle << std::setfill('0') << std::setw(2) << timeLimit / 60000;
        windowTitle << ":";
        windowTitle << std::setfill('0') << std::setw(2) << (timeLimit / 1000) % 60;

        windowTitle << "  Posizione: (";
        windowTitle << pos.first << ", ";
        windowTitle << pos.second << ")";

        /*float camPos[3] = {0, 0, 0};
        g_camera.GetPos(camPos[0], camPos[1], camPos[2]);
        windowTitle << " [" << camPos[0] << ", " << camPos[1] << ", " << camPos[2] << "]";*/

        windowTitle << "  Allarmi rimanenti: " << m_maze->getAlarmCount();

        glutSetWindowTitle(windowTitle.str().c_str());
    }
}

void GlutFunctions::GameOver(bool win) {
    std::stringstream windowTitle;
    if (!win) windowTitle << "Tempo Scaduto! Hai perso!";
    else windowTitle << "Hai vinto!!!";
    windowTitle << " Premi SPAZIO per cominciare una nuova partita.";
    AudioFunctions::StopAll();
    AudioFunctions::ResetSources();

    g_fps_mode = false;
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    glutSetWindowTitle(windowTitle.str().c_str());
    InitGame();
}

void GlutFunctions::Idle() {
    Display();
}

void GlutFunctions::Mouse(int button, int state, int, int) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}

void GlutFunctions::MouseMotion(int x, int y) {
    if (just_warped) {
        just_warped = false;
        return;
    }

    if (g_fps_mode) {
        int dx = x - g_viewport_width / 2;
        int dy = y - g_viewport_height / 2;

        if (dx) {
            g_camera.RotateYaw(g_rotation_speed * dx);
        }

        if (dy) {
            g_camera.RotatePitch(g_rotation_speed * dy);
        }

        glutWarpPointer(g_viewport_width / 2, g_viewport_height / 2);

        just_warped = true;
    }
}

void GlutFunctions::Cleanup() {
    delete m_maze;
    TextureFunctions::ResetTextures();
    AudioFunctions::StopAll();
    AudioFunctions::ResetSources();
}