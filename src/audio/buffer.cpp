//
// Created by Admin on 04/06/2016.
//

#include <AL/alut.h>
#include "buffer.h"


audio::buffer::buffer(ALuint bufferID) : id(bufferID) {
    //alGenBuffers(1, &id);
    //id = alutCreateBufferFromFile(buffer.c_str());
}

ALuint audio::buffer::getID() const {
    return id;
}

/*audio::buffer::~buffer() {
    alDeleteBuffers(1, &id);
}*/

void audio::buffer::release() {
    alDeleteBuffers(1, &id);
    id = 0;
}