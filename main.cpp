#include <GL/glut.h>
#include <iostream>
#include <AL/alut.h>

#include "GlutFunctions.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    alutInit(&argc, argv);
    GlutFunctions::Init();
    return 0;
}
/*
#include <AL/alut.h>
#include <iostream>

int main(int argc, char **argv) {
    if (!alutInit (&argc, argv))
    {
        ALenum error = alutGetError ();
        fprintf (stderr, "%s\n", alutGetErrorString (error));
        exit (EXIT_FAILURE);
    }


    ALuint buffer;
    ALuint source;
    ALenum error;
    ALint status;

    // Create an AL buffer from the given sound file.
    buffer = alutCreateBufferFromFile ("res/test2.wav");
    if (buffer == AL_NONE)
    {
        error = alutGetError ();
        fprintf (stderr, "Error loading file: '%s'\n",
                 alutGetErrorString (error));
        alutExit ();
        exit (EXIT_FAILURE);
    }

    // Generate a single source, attach the buffer to it and start playing.
    alGenSources (1, &source);
    alSourcei (source, AL_BUFFER, buffer);


    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, -10.0f, 0.0f, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    alSource3f(source, AL_POSITION, 0.0, 0, -1.0f);
    alSourcei(source, AL_LOOPING, AL_TRUE);

    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    //alSourcef(source, AL_REFERENCE_DISTANCE, 1.0);
    //alSourcef(source, AL_MAX_DISTANCE, 2.0f);

    alSourcePlay (source);

    // Normally nothing should go wrong above, but one never knows...
    error = alGetError ();
    if (error != ALUT_ERROR_NO_ERROR)
    {
        fprintf (stderr, "%s\n", alGetString (error));
        alutExit ();
        exit (EXIT_FAILURE);
    }

    float initPos = -10.0f;

    // Check every 0.1 seconds if the sound is still playing.
    do
    {
        alutSleep (0.1f);
        initPos += 0.2f;
        alListener3f(AL_POSITION, initPos, 0, 0.0f);
        alGetSourcei (source, AL_SOURCE_STATE, &status);
    }
    while (status == AL_PLAYING && initPos < 10.0f);
}*/