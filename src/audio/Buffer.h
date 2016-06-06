//
// Created by Admin on 04/06/2016.
//

#pragma once


#include <AL/al.h>
#include <string>

namespace audio {
    class Buffer {
    private:
        ALuint id_;
    public:
        Buffer(ALuint bufferID);

        Buffer() {};

        ALuint getID() const;

        void release();

    };
}
