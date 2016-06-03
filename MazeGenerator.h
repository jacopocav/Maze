//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <random>
#include "Maze.h"

class MazeGenerator {
private:
    enum Direction {
        N, S, E, W
    };

    // Per generare interi casuali
    static std::default_random_engine rnd;

    // Per generare numeri reali casuali in [0,1)
    static std::uniform_real_distribution<float> distribution;

    // Indica se il labirinto dev'essere senza vicoli ciechi o meno (letto da file)
    static bool braided;

    // Livello di casualità nella scelta di celle all'interno dell'algoritmo di generazione (letto da file)
    static const float randomness;

    // Rimuove un vicolo cieco dal labirinto (se la cella è effettivamente il termine di un vicolo cieco)
    static void cullDeadEnd(Maze *maze, Coordinates cell);
public:
    // Genera un labirinto con le dimensioni passate per parametro
    static Maze* generateMaze(unsigned height, unsigned width);

    // Aggiunge un determinato numero di allarmi al labirinto, in posizione casuale
    static void addAlarmsToMaze(Maze *maze, int alarmCount);
};
