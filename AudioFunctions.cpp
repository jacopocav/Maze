//
// Created by Admin on 30/05/2016.
//

#include <AL/al.h>
#include <AL/alut.h>
#include <iostream>
#include "AudioFunctions.h"

ALuint buffer;
ALuint source;
ALenum error;

void AudioFunctions::Init() {
    buffer = alutCreateBufferFromFile("res/audio/test2.wav");
    if (buffer == AL_NONE) {
        error = alutGetError();
        fprintf(stderr, "Error loading file: '%s'\n",
                alutGetErrorString(error));
        alutExit();
        exit(EXIT_FAILURE);
    }

    // Generate a single source, attach the buffer to it and start playing.
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE);
    alDistanceModel(AL_INVERSE_DISTANCE);
    alSourcef(source, AL_REFERENCE_DISTANCE, 0.8f);
    alSourcef(source, AL_ROLLOFF_FACTOR, 2.0f);
    alSourcePlay(source);
}

void AudioFunctions::SetSourcePosition(float x, float y, float z) {
    alSource3f(source, AL_POSITION, x, y, z);
}

void AudioFunctions::SetListenerOrientation(float atx, float aty, float atz, float upx, float upy, float upz) {
    float ori[6] = {atx, aty, atz, upx, upy, upz};
    alListenerfv(AL_ORIENTATION, ori);
}

void AudioFunctions::SetListenerPosition(float x, float y, float z) {
    alListener3f(AL_POSITION, x, y, z);
}
