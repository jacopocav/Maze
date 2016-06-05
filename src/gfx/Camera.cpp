#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

const float gfx::Camera::PI = 3.14159265358979323846f;
const float gfx::Camera::PI_2 = 1.57079632679f;

void gfx::Camera::init() {
    yaw_ = 0.0;
    pitch_ = 0.0;

    setPos(0, 0, 0);
}

void gfx::Camera::refresh() {
    // gfx::Camera parameter according to Riegl's co-ordinate system
    // x/y for flat, z for height
    lx_ = cosf(yaw_) * cosf(pitch_);
    ly_ = sinf(pitch_);
    lz_ = sinf(yaw_) * cosf(pitch_);

    strafeLx_ = cosf(yaw_ - PI_2);
    strafeLz_ = sinf(yaw_ - PI_2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    y_ = y_ + incr*ly;
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

void gfx::Camera::rotateYaw(float angle) {
    yaw_ += angle;

    refresh();
}

void gfx::Camera::rotatePitch(float angle) {
    const float limit = 60.0f * PI / 180.0f;

    pitch_ -= angle;

    if (pitch_ < -limit)
        pitch_ = -limit;

    if (pitch_ > limit)
        pitch_ = limit;

    refresh();
}

void gfx::Camera::setYaw(float angle) {
    yaw_ = angle;

    refresh();
}

void gfx::Camera::setPitch(float angle) {
    pitch_ = angle;

    refresh();
}
