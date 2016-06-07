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
    // InputCallbacks può accedere ai membri privati di questa classe
    friend class InputCallbacks;

private:
    // Prepara l'ambiente per l'inizio di una nuova partita
    static void initGame();

    // Aggiorna lo stato di gioco: tempo rimanente, titolo della finestra,
    // e innesca il game over se le condizioni sono state raggiunte
    static void updateGameStatus(int timeDiff);

    // Termina la partita mostrando un messaggio di vittoria o di sconfitta nel titolo della finestra
    static void gameOver(bool win);

    // Libera la memoria prima della chiusura del gioco
    static void cleanup();

    // Prodotto vettoriale tra 2 vettori
    static std::vector<float> crossVector(const std::vector<float> &a, const std::vector<float> &b);

    // Tempo rimanente alla fine della partita (in ms)
    static int remainingTime_;
    static audio::Manager audioManager_;
    static game::Maze *maze_;
    // Posizione della luce (costante perché corrisponde sempre a quella della camera)
    static const float lightPos_[4];

    // Dimensioni del labirinto e numero di allarmi (lette dalle impostazioni)
    static const unsigned MAZE_HEIGHT, MAZE_WIDTH;
    static const int ALARM_COUNT;

public:
    // Inizializza l'ambiente Glut
    static void init();

    // Callback per glutDisplayFunc
    static void display();
    // Callback per glutReshapeFunc
    static void reshape(int width, int height);
    // Callback per glutIdleFunc
    static void idle();
};
