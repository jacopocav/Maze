//
// Created by Admin on 05/06/2016.
//

#pragma once

#include <memory>
#include "Maze.h"

namespace game {
    // Classe statica che gestisce gli aspetti relativi al tempo di gioco
    class Time {
    public:
        // Calcola un tempo limite ragionevole per la risoluzione del labirinto, partendo dalla posizione currentPos
        // Se il labirinto è senza vicoli ciechi, il tempo viene calcolato in basa alla distanza Manhattan media
        // da tutti gli allarmi, altrimenti viene considerata la lunghezza media dei percorsi dalla posizione
        // corrente verso tutti gli allarmi.
        static int getTimeLimit(std::shared_ptr<Maze> maze, const Coordinates &currentPos);
        // Calcola la distanza Manhattan tra due celle del labirinto (somma delle differenze di coordinate)
        static int manhattanDistance(const Coordinates &pos1, const Coordinates &pos2);
        // Ritorna l'orario di sistema, in millisecondi dall'epoch time
        static int getCurrentTimeMillis();
    };

}
