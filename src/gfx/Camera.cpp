#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

void gfx::Camera::init() {
    yaw_ = 0.0;
    pitch_ = 0.0;

    setPos(0, 0, 0);
}

void gfx::Camera::refresh() {
    // Calcolo del vettore di direzione a partire dagli angoli yaw e pitch
    // http://learnopengl.com/#!Getting-started/Camera
    lx_ = cosf(yaw_) * cosf(pitch_);
    ly_ = sinf(pitch_);
    lz_ = sinf(yaw_) * cosf(pitch_);

    // Calcolo del vettore di spostamento laterale
    strafeLx_ = sinf(yaw_);
    strafeLz_ = - 1.0f * cosf(yaw_);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Cambia posizione e orientamento della telecamera
    // Primi 3 parametri: posizione
    // Secondi 3 parametri: direzione
    // Ultimi 3 parametri: vettore che indica l'"alto" (costante perché la telecamera non può effettuare rollii)
    gluLookAt(x_, y_, z_, x_ + lx_, y_ + ly_, z_ + lz_, 0.0, 1.0, 0.0);

}

void gfx::Camera::setPos(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;

    refresh();
}

void gfx::Camera::getPos(float &x, float &y, float &z) {
    x = x_;
    y = y_;
    z = z_;
}

void gfx::Camera::getDirectionVector(float &x, float &y, float &z) {
    x = lx_;
    y = ly_;
    z = lz_;
}

void gfx::Camera::move(float incr) {
    float lx = cosf(yaw_) * cosf(pitch_);
    float ly = sinf(pitch_);
    float lz = sinf(yaw_) * cosf(pitch_);

    x_ = x_ + incr * lx;
    y_ = y_ + incr * ly;
    z_ = z_ + incr * lz;

    refresh();
}

void gfx::Camera::strafe(float incr) {
    x_ = x_ + incr * strafeLx_;
    z_ = z_ + incr * strafeLz_;

    refresh();
}

void gfx::Camera::fly(float incr) {
    y_ = y_ + incr;

    refresh();
}

void gfx::Camera::rotateYaw(float radAngle) {
    yaw_ += radAngle;

    refresh();
}

void gfx::Camera::rotatePitch(float radAngle) {
    // L'angolo verticale massimo è di 60° (in entrambe le direzioni, quindi in totale 120°)
    // Se non ci fosse un limite, la telecamera potrebbe girarsi verticalmente all'infinito
    // (poco realistico, visto che si sta simulando lo sguardo umano)
    const float limit = 60.0f * constants::PI / 180.0f;

    pitch_ -= radAngle;

    if (pitch_ < -limit)
        pitch_ = -limit;

    if (pitch_ > limit)
        pitch_ = limit;

    refresh();
}

void gfx::Camera::setYaw(float radAngle) {
    yaw_ = radAngle;

    refresh();
}

void gfx::Camera::setPitch(float radAngle) {
    pitch_ = radAngle;

    refresh();
}
