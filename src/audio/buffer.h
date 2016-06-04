//
// Created by Admin on 04/06/2016.
//

#pragma once


#include <AL/al.h>
#include <string>

namespace audio {
    class buffer {
    private:
        ALuint id;
    public:
        buffer(ALuint bufferID);

        //~buffer();

        ALuint getID() const;

        void release();

    };
}
