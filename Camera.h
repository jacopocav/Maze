#pragma once

/*
Generic camera class by Nghia Ho
*/

class Camera {
public:
    Camera() { Init(); }

    virtual ~Camera() { }

    static const float M_PI;
    static const float M_PI_2;

    void Init();

    void Refresh();

    void SetPos(float x, float y, float z);

    void GetPos(float &x, float &y, float &z);

    void GetDirectionVector(float &x, float &y, float &z);

    void SetYaw(float angle);

    void SetPitch(float angle);

    // Navigation
    virtual void Move(float incr);

    virtual void Strafe(float incr);

    virtual void Fly(float incr);

    void RotateYaw(float angle);

    void RotatePitch(float angle);

protected:
    float m_x, m_y, m_z;   // Position
    float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
    float m_yaw, m_pitch; // Various rotation angles
    float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
};