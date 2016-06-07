//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <vector>

namespace game {

    // Viene utilizzato questo tipo per indicare le coordinate di una cella nel labirinto
    typedef std::pair<unsigned, unsigned> Coordinates;

    // Classe che modella un labirinto
    class Maze {
        // MazeGenerator può accedere ai membri privati di Maze,
        // per poter generare il labirinto e aggiungere gli allarmi
        friend class MazeGenerator;

    private:
        // Vettore bidimensionale di booleani che rappresentano la struttura del labirinto
        // false = muro, true = libero
        std::vector<std::vector<bool>> maze_;

        // Di utilità al metodo pathLength, serve a tenere traccia delle celle percorse
        // durante la ricerca di una strada
        std::vector<std::vector<bool>> wasHere_;

        // Vettore contenente le posizioni degli allarmi del labirinto
        std::vector<Coordinates> alarms_;

        // Vero se il labirinto è "braided", ovvero senza vicoli ciechi
        bool isBraided_;

        // Funzione ricorsiva ausiliaria, usata da pathLength
        bool recursiveSolve(int x, int y, int endX, int endY);

        // Costruisce un labirinto di altezza e larghezza definite (se le dimensioni non sono dispari,
        // vengono incrementate di 1.
        // Il labirinto creato è di soli muri.
        // Il costruttore è privato perché i labirinti vanno creati esclusivamente con MazeGenerator
        Maze(unsigned height, unsigned width);
    public:

        int getHeight() const;

        int getWidth() const;

        // Ritornano il valore di una cella (false = muro, true = libera)
        bool get(int row, int col) const;
        bool get(Coordinates coord) const;

        // Rimuove l'allarme alle coordinate pos (se presente)
        void removeAlarm(Coordinates pos);

        // Ritorna il numero di allarmi presenti
        int getAlarmCount() const;

        // Ritorna la posizione dell'allarme di indice index
        // Se non esiste, ritorna (-1, -1)
        Coordinates getAlarm(int index) const;

        // Ritornano true se in corrispondenza delle coordinate passate è presente un allarme
        bool isAlarm(unsigned row, unsigned col) const;
        bool isAlarm(Coordinates pos) const;

        // Ritorna true se il labirinto è senza vicoli ciechi
        bool isBraided() const;

        // Ritorna la lunghezza del percorso da start a end
        // Se il labirinto non ha vicoli ciechi, il percorso calcolato
        // non corrisponde necessariamente a quello più breve.
        int pathLength(Coordinates start, Coordinates end);
    };
}