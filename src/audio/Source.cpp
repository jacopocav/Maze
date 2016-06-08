#include "Source.h"


audio::Source::Source(ALuint sourceID, const audio::Buffer &buffer) : id_(sourceID), buffer_(buffer) {
    alSourcei(id_, AL_BUFFER, buffer_.getID());
    alSourcei(id_, AL_LOOPING, AL_TRUE);
    alSourcei(id_, AL_SOURCE_RELATIVE, AL_FALSE);
    alSourcef(id_, AL_REFERENCE_DISTANCE, 0.8f);
    alSourcef(id_, AL_ROLLOFF_FACTOR, 2.0f);
}

void audio::Source::setPosition(float posX, float posY, float posZ) {
    alSource3f(id_, AL_POSITION, posX, posY, posZ);
}

void audio::Source::play() {
    alSourcePlay(id_);
}

void audio::Source::pause() {
    alSourcePause(id_);
}

void audio::Source::stop() {
    alSourceStop(id_);
}

void audio::Source::setPitch(float pitch){
    alSourcef(id_, AL_PITCH, pitch);
}

ALuint audio::Source::getId() const {
    return id_;
}

void audio::Source::release() {
    alSourcei(id_, AL_BUFFER, 0);
    alDeleteSources(1, &id_);
}