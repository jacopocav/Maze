#pragma once

#include <memory>
#include "Camera.h"
#include "../game/Maze.h"

namespace gfx {
    // Estensione di Camera a cui aggiunge il rilevamento delle collisioni contro i muri del labirinto
    class MazeCamera : public Camera {
    private:
        // Labirinto associato alla telecamera (per il rilevamento delle collisioni)
        std::shared_ptr<game::Maze> maze_;
        // Ritorna true se la telecamera si trova entro i limiti estremi del labirinto
        bool checkBounds();


    public:
        MazeCamera(std::shared_ptr<game::Maze> maze) : maze_(maze), Camera() { }

        virtual void move(float incr);

        virtual void strafe(float incr);

        virtual void fly(float incr);

        // Ritorna la posizione nel labirinto della telecamera
        game::Coordinates getMazeCoordinates();

        // Associa un nuovo labirinto alla telecamera
        void setMaze(std::shared_ptr<game::Maze> maze);



    };
}