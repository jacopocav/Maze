#pragma once

namespace gfx {
    class Camera {
    public:
        Camera() { init(); }

        virtual ~Camera() { }

        static const float PI; // Pi greco
        static const float PI_2; // Pi/2

        // Inizializza la posizione e la rotazione della camera
        void init();
        // Aggiorna posizione e orientamento della camera
        void refresh();

        void setPos(float x, float y, float z);

        void getPos(float &x, float &y, float &z);

        void getDirectionVector(float &x, float &y, float &z);

        void setYaw(float angle);

        void setPitch(float angle);

        // Navigation
        virtual void move(float incr);

        virtual void strafe(float incr);

        virtual void fly(float incr);

        void rotateYaw(float angle);

        void rotatePitch(float angle);

    protected:
        float x_, y_, z_;   // Position
        float lx_, ly_, lz_; // Direction vector of where we are looking at
        float yaw_, pitch_; // Various rotation angles
        float strafeLx_, strafeLz_; // Always 90 degree to direction vector
    };
}