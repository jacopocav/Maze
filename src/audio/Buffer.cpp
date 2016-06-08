#include <AL/alut.h>
#include "Buffer.h"


audio::Buffer::Buffer(ALuint bufferID) : id_(bufferID) {}

ALuint audio::Buffer::getID() const {
    return id_;
}

void audio::Buffer::release() {
    alDeleteBuffers(1, &id_);
    id_ = 0;
}
