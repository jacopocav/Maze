//
// Created by Admin on 04/06/2016.
//

#include "source.h"


audio::source::source(ALuint sourceID, const audio::buffer &buf) : id(sourceID), buffer(buf) {
    //alGenSources(1, &id);
    alSourcei(id, AL_BUFFER, buffer.getID());
    alSourcei(id, AL_LOOPING, AL_TRUE);
    alSourcei(id, AL_SOURCE_RELATIVE, AL_FALSE);
    alSourcef(id, AL_REFERENCE_DISTANCE, 0.8f);
    alSourcef(id, AL_ROLLOFF_FACTOR, 2.0f);
}

void audio::source::setPosition(float posX, float posY, float posZ) {
    alSource3f(id, AL_POSITION, posX, posY, posZ);
}

void audio::source::play() {
    alSourcePlay(id);
}

void audio::source::pause() {
    alSourcePause(id);
}

void audio::source::stop() {
    alSourceStop(id);
}

void audio::source::setPitch(float pitch){
    alSourcef(id, AL_PITCH, pitch);
}

/*audio::source::~source() {
    stop();
    alSourcei(id, AL_BUFFER, 0);
    alDeleteSources(1, &id);
}*/

ALuint audio::source::getId() const {
    return id;
}

void audio::source::release() {
    alSourcei(id, AL_BUFFER, 0);
    alDeleteSources(1, &id);
}