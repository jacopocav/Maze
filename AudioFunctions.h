//
// Created by Admin on 30/05/2016.
//

#pragma once


class AudioFunctions {
public:
    static void Init();
    static void PlaySource();
    static void PauseSource();

    static void SetSourcePosition(float x, float y, float z);
    static void SetListenerPosition(float x, float y, float z);
    static void SetListenerOrientation(float atx, float aty, float atz, float upx, float upy, float upz);

};
