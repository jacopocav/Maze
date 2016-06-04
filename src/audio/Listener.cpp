//
// Created by Admin on 04/06/2016.
//

#include <AL/al.h>
#include "listener.h"


void audio::listener::SetOrientation(float atx, float aty, float atz, float upx, float upy, float upz) {
    float ori[6] = {atx, aty, atz, upx, upy, upz};
    alListenerfv(AL_ORIENTATION, ori);
}

void audio::listener::SetPosition(float x, float y, float z) {
    alListener3f(AL_POSITION, x, y, z);
}
