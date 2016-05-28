#include <GL/glut.h>
#include <iostream>

#include "GlutFunctions.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutFunctions::Init();
    return 0;
}

/*int main(){
    ALCcontext * Context;
    ALCdevice * Device;
    Device = alcOpenDevice(NULL);

    if(Device == NULL){
        exit(-1);
    }

    Context = alcCreateContext(Device, NULL);
    alcMakeContextCurrent(Context);

    alGetError();

    char* alBuffer; //data for the buffer

    ALenum alFormatBuffer; //for the buffer format

    ALsizei alFreqBuffer; //for the frequency of the buffer

    long alBufferLen; //the bit depth

    ALboolean alLoop; //looped

    unsigned int alSource; //buffer source

    unsigned int alSampleSet;


}*/