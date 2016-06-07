//
// Created by Admin on 24/05/2016.
//
#include <sstream>
#include <iomanip>
#include <cmath>

#include <GL/freeglut.h>
#include <chrono>

#include "GlutCallbacks.h"
#include "gfx/Textures.h"
#include "gfx/Drawing.h"
#include "game/Settings.h"
#include "audio/Listener.h"
#include "game/Time.h"
#include "InputCallbacks.h"

std::shared_ptr<game::Maze> GlutCallbacks::maze_;
int GlutCallbacks::remainingTime_;

audio::Manager GlutCallbacks::audioManager_;

const float GlutCallbacks::lightPos_[4] = {0.0f, 0.0f, 0.0f, 1.0f};

const unsigned GlutCallbacks::MAZE_HEIGHT = static_cast<unsigned>(game::Settings::getInstance()["MAZE_SIZE_X"]);
const unsigned GlutCallbacks::MAZE_WIDTH = static_cast<unsigned>(game::Settings::getInstance()["MAZE_SIZE_Y"]);
const int GlutCallbacks::ALARM_COUNT = game::Settings::getInstance()["ALARM_COUNT"];

void GlutCallbacks::initGame() {
    // Generazione nuovo labirinto

    maze_ = game::MazeGenerator::generateMaze(MAZE_HEIGHT, MAZE_WIDTH);
    game::MazeGenerator::addAlarmsToMaze(maze_, ALARM_COUNT);

    // Aggiunta sorgenti audio agli allarmi del labirinto
    audioManager_.bindSources(maze_);

    // Inizializzazione camera
    InputCallbacks::camera_.setMaze(maze_);
    InputCallbacks::camera_.init();

    // Aggiornamento tempi
    remainingTime_ = game::Time::getTimeLimit(maze_, game::Coordinates(1, 1));
    InputCallbacks::currTime_ = game::Time::getCurrentTimeMillis();
}

void GlutCallbacks::updateGameStatus(int timeDiff) {
    game::Coordinates pos = InputCallbacks::camera_.getMazeCoordinates();

    remainingTime_ -= timeDiff;

    std::stringstream windowTitle; // Testo da scrivere sulla barra del titolo della finestra

    if (maze_->isAlarm(pos)) { // In posizione corrente c'è un allarme: va rimosso
        maze_->removeAlarm(pos);
        audioManager_.eraseSound(pos);
        if (maze_->getAlarmCount() > 0) { // Aggiorna il tempo rimanente
            remainingTime_ = std::max(remainingTime_, game::Time::getTimeLimit(maze_, pos));
        }
        else gameOver(true); // Se gli allarmi sono finiti, il gioco è finito con vittoria
    } else if (remainingTime_ <= 0) { // Tempo scaduto, gioco finito con fallimento
        gameOver(false);
    } else {
        windowTitle << "Tempo: ";
        windowTitle << std::setfill('0') << std::setw(2) << remainingTime_ / 60000;
        windowTitle << ":";
        windowTitle << std::setfill('0') << std::setw(2) << (remainingTime_ / 1000) % 60;

        windowTitle << "  Posizione: (";
        windowTitle << pos.first << ", ";
        windowTitle << pos.second << ")";

        windowTitle << "  Allarmi rimanenti: " << maze_->getAlarmCount();

        glutSetWindowTitle(windowTitle.str().c_str());
    }
}

void GlutCallbacks::gameOver(bool win) {
    std::stringstream windowTitle;
    if (!win) windowTitle << "Tempo Scaduto! Hai perso!";
    else windowTitle << "Hai vinto!!!";
    windowTitle << " Premi SPAZIO per cominciare una nuova partita.";

    audioManager_.releaseSounds(); // Vengono eliminate le sorgenti audio degli allarmi

    // Ritorno allo stato iniziale
    InputCallbacks::movement_ = false;
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    glutSetWindowTitle(windowTitle.str().c_str());
    initGame();
}

void GlutCallbacks::cleanup() {
    // Vengono cancellati il labirinto, le texture, buffer e sorgenti audio
    gfx::Textures::resetTextures();
    audioManager_.releaseSounds();
}

std::vector<float> GlutCallbacks::crossVector(const std::vector<float> &a, const std::vector<float> &b) {
    std::vector<float> result(a.size());
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}

void GlutCallbacks::init() {
    // Impostazione di MSAA
    int AAFactor = game::Settings::getInstance()["MULTISAMPLING"];
    if (AAFactor % 2 != 0) {
        AAFactor -= AAFactor % 2;
    }
    if (AAFactor > 0) {
        glutSetOption(GLUT_MULTISAMPLE, 4);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glEnable(GLUT_MULTISAMPLE);
    } else {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    }
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Premi SPAZIO per iniziare");

    glutIgnoreKeyRepeat(1);
    glClearColor(0, 0, 0, 1.0f);

    // Assegnazione callback
    glutDisplayFunc(GlutCallbacks::display);
    glutIdleFunc(GlutCallbacks::idle);
    glutReshapeFunc(GlutCallbacks::reshape);
    glutMouseFunc(InputCallbacks::mouse);
    glutMotionFunc(InputCallbacks::mouseMotion);
    glutPassiveMotionFunc(InputCallbacks::mouseMotion);
    glutKeyboardFunc(InputCallbacks::keyboard);
    glutKeyboardUpFunc(InputCallbacks::keyboardUp);
    glutSpecialFunc(InputCallbacks::keyboardSpecial);
    glutSpecialUpFunc(InputCallbacks::keyboardSpecialUp);
    glutTimerFunc(16, InputCallbacks::timer, 0);

    // Configurazione camera
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();

    // Configurazione illuminazione
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    GLfloat black[4] = {0, 0, 0, 1};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

    const float ambient_light[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    const float diffuse_light[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    const float specular_light[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    float attenuation = 1.5f;
    if(game::Settings::getInstance()["DISABLE_LIGHT_ATTENUATION"] == 1)
        attenuation = 0.0f;
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation);

    const float material[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_SPECULAR, material);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
    glMateriali(GL_FRONT, GL_SHININESS, 32);

    // Configurazione texture
    glEnable(GL_TEXTURE_2D);

    gfx::Textures::initTextures(3);
    gfx::Textures::readFromBMP("res/texture/alt_floor.bmp", "floor");
    gfx::Textures::readFromBMP("res/texture/lux_wall.bmp", "wall");
    gfx::Textures::readFromBMP("res/texture/lux_ceil.bmp", "ceil");

    initGame();

    glutMainLoop();
}


void GlutCallbacks::display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    InputCallbacks::camera_.refresh();

    float cpos[3] = {0, 0, 0};
    InputCallbacks::camera_.getPos(cpos[0], cpos[1], cpos[2]);
    // Fa corrispondere la posizione dell'ascoltatore con quella della camera
    audio::Listener::setPosition(cpos[0], cpos[1], cpos[2]);

    std::vector<float> at = {0, 0, 0};
    InputCallbacks::camera_.getDirectionVector(at[0], at[1], at[2]);
    // OpenAL richiede che i vettori che definiscono l'orientamento dell'ascoltatore siano ortogonali tra loro
    // Questo invece non è richiesto da OpenGL, quindi bisogna prima calcolare il vettore up in modo che sia
    // ortogonale a quello at (che viene fornito già normalizzato dalla camera)

    // Vettore perpendicolare ad at e all'asse y
    auto right = crossVector(at, {0, 1, 0});
    // Vettore perpendicolare al piano dell'"orizzonte" di visione
    auto up = crossVector(right, at);
    // Fa corrispondere l'orientamento dell'ascoltatore con quello della camera
    audio::Listener::setOrientation(at[0], at[1], at[2], up[0], up[1], up[2]);

    // La traslazione è necessaria per mettere il giocatore dentro il labirinto
    // (Altrimenti inizierebbe dentro a un muro)
    glTranslatef(-0.6f, 0, 0.6);

    glPushMatrix();
    glLoadIdentity();
    // La luce deve trovarsi sempre in corrispondenza della camera
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos_);
    glPopMatrix();

    game::Coordinates pos = InputCallbacks::camera_.getMazeCoordinates();

    // Disegna la porzione di labirinto circostante al giocatore
    gfx::Drawing::drawMaze(maze_, pos.first, pos.second);

    glutSwapBuffers();
}


void GlutCallbacks::reshape(int width, int height) {
    InputCallbacks::viewportWidth_ = width;
    InputCallbacks::viewportHeight_ = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    // Imposta la prospettiva (angolo di visione verticale, rapporto d'aspetto, distanza piano near, distanza piano far)
    // Utilizza internamente glFrustum
    gluPerspective(45, aspectRatio, 0.001, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void GlutCallbacks::idle() {
    display();
}

