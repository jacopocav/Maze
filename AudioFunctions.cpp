//
// Created by Admin on 30/05/2016.
//

#include <AL/al.h>
#include <AL/alut.h>
#include <iostream>
#include "AudioFunctions.h"

ALuint *AudioFunctions::sources;
ALuint *AudioFunctions::buffers;
int AudioFunctions::sourceCount;
std::map<std::string, int> AudioFunctions::sourceTable;

void AudioFunctions::InitSources(int srcCount) {
    sources = new ALuint[srcCount];
    buffers = new ALuint[srcCount];
    alGenSources(srcCount, sources);
    alGenBuffers(srcCount, buffers);
    sourceCount = srcCount;
    alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
    //alListenerf(AL_MAX_DISTANCE, 2.0f);
}

void AudioFunctions::SetListenerOrientation(float atx, float aty, float atz, float upx, float upy, float upz) {
    float ori[6] = {atx, aty, atz, upx, upy, upz};
    alListenerfv(AL_ORIENTATION, ori);
}

void AudioFunctions::SetListenerPosition(float x, float y, float z) {
    alListener3f(AL_POSITION, x, y, z);
}

void AudioFunctions::PlaySource(std::string name) {
    if(sourceTable.find(name) != sourceTable.end())
        alSourcePlay(sources[sourceTable[name]]);
}

void AudioFunctions::PauseSource(std::string name) {
    if(sourceTable.find(name) != sourceTable.end())
        alSourcePause(sources[sourceTable[name]]);
}

void AudioFunctions::SetSourcePosition(std::string name, float x, float y, float z) {
    if(sourceTable.find(name) != sourceTable.end())
        alSource3f(sources[sourceTable[name]], AL_POSITION, x, y, z);
}



void AudioFunctions::LoadSourceFromFile(std::string path, int sourceIndex, std::string name, bool looping,
                                       float pitch) {
    buffers[sourceIndex] = alutCreateBufferFromFile(path.c_str());
    alSourcei(sources[sourceIndex], AL_BUFFER, buffers[sourceIndex]);
    sourceTable[name] = sourceIndex;
    if(looping) alSourcei(sources[sourceIndex], AL_LOOPING, AL_TRUE);
    alSourcei(sources[sourceIndex], AL_SOURCE_RELATIVE, AL_FALSE);
    alSourcef(sources[sourceIndex], AL_REFERENCE_DISTANCE, 0.8f);
    alSourcef(sources[sourceIndex], AL_ROLLOFF_FACTOR, 2.0f);
    alSourcef(sources[sourceIndex], AL_PITCH, pitch);

}

void AudioFunctions::PlayAll() {
    for(auto it = sourceTable.begin(); it != sourceTable.end(); ++it){
        alSourcePlay(sources[it->second]);
    }
}

void AudioFunctions::PauseAll() {
    for(auto it = sourceTable.begin(); it != sourceTable.end(); ++it){
        alSourcePause(sources[it->second]);
    }
}

void AudioFunctions::RemoveSource(std::string name){
    if(sourceTable.find(name) != sourceTable.end()) {
        alSourceStop(sources[sourceTable[name]]);
        alSourcei(sources[sourceTable[name]], AL_BUFFER, 0);
        alDeleteBuffers(1, &buffers[sourceTable[name]]);
        alDeleteSources(1, &sources[sourceTable[name]]);
    }

}