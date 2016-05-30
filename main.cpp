#include <GL/glut.h>
#include <iostream>

#include "GlutFunctions.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutFunctions::Init();
    return 0;
}

/*#include <AL/alut.h>
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
    buffer = alutCreateBufferFromFile ("res/test.wav");
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
    alSourcePlay (source);

    // Normally nothing should go wrong above, but one never knows...
    error = alGetError ();
    if (error != ALUT_ERROR_NO_ERROR)
    {
        fprintf (stderr, "%s\n", alGetString (error));
        alutExit ();
        exit (EXIT_FAILURE);
    }

    // Check every 0.1 seconds if the sound is still playing.
    do
    {
        alutSleep (0.1f);
        alGetSourcei (source, AL_SOURCE_STATE, &status);
    }
    while (status == AL_PLAYING);
}*/