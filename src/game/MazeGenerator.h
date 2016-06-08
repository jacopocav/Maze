#pragma once


#include <random>
#include <memory>
#include "Maze.h"

namespace game {
    // Classe statica che permette di generare labirinti casuali
    class MazeGenerator {
    private:
        enum Direction {
            N, S, E, W
        };

        // Per generare interi casuali
        static std::default_random_engine rndEngine_;

        // Per generare numeri reali casuali in [0,1)
        static std::uniform_real_distribution<float> distribution_;

        // Indica se il labirinto dev'essere senza vicoli ciechi o meno (letto da file)
        static bool braidedMaze_;

        // Livello di casualità nella scelta di celle all'interno dell'algoritmo di generazione (letto da file)
        static const float mazeRandomness_;

        // Rimuove un vicolo cieco dal labirinto (se la cella è effettivamente il termine di un vicolo cieco)
        static void cullDeadEnd(std::shared_ptr<Maze> maze, Coordinates cell);

    public:
        // Genera un labirinto con le dimensioni passate per parametro
        // Implementa il Growing Tree Algorithm
        // Tratto da: http://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm
        static std::shared_ptr<Maze> generateMaze(unsigned height, unsigned width);

        // Aggiunge un determinato numero di allarmi al labirinto, in posizione casuale
        static void addAlarmsToMaze(std::shared_ptr<Maze> maze, int alarmCount);
    };
}