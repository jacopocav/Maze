#pragma once

namespace constants {
    // Costante Pi greco
    const float PI = 4.0f * atanf(1);
}

namespace gfx {
    // Classe che gestisce la telecamera di OpenGL
    class Camera {
        friend class MazeCamera;

    private:
        // Posizione
        float x_, y_, z_;
        // Componenti del vettore normalizzato di direzione dello sguardo
        float lx_, ly_, lz_;
        // Angoli di imbardata (rotazione orizzontale) e beccheggio (rotazione verticale)
        float yaw_, pitch_;
        // Componenti del vettore orizzontale e perpendicolare a quello dello sguardo (usato per il movimento laterale)
        float strafeLx_, strafeLz_;
    public:
        Camera() { init(); }

        // Distruttore virtuale per permettere ereditarietà
        virtual ~Camera() { }

        // Inizializza la posizione e la rotazione della camera
        void init();

        // Aggiorna posizione e orientamento della camera
        void refresh();

        // Imposta e aggiorna la posizione della telecamera (invoca refresh)
        void setPos(float x, float y, float z);

        // Modifica le variabili passate per riferimento in modo che siano uguali alla posizione della telecamera
        void getPos(float &x, float &y, float &z);

        // Modifica le variabili passate per riferimento in modo che rappresentino il vettore di direzione della camera
        void getDirectionVector(float &x, float &y, float &z);

        // Imposta l'angolo di imbardata (rotazione orizzontale, in radianti)
        void setYaw(float radAngle);

        // Imposta l'angolo di beccheggio (rotazione verticale, in radianti)
        void setPitch(float radAngle);

        // Muove la telecamera avanti o indietro secondo la sua direzione
        virtual void move(float incr);

        // Muove la telecamera orizzontalmente e in direzione perpendicolare alla sua direzione
        virtual void strafe(float incr);

        // Muove la telecamera lungo l'asse y
        virtual void fly(float incr);

        // Ruota orizzontalmente la telecamera di un certo angolo (in radianti)
        void rotateYaw(float radAngle);

        // Ruota verticalmente la telecamera di un certo angolo (in radianti)
        void rotatePitch(float radAngle);

    };
}