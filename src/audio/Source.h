//
// Created by Admin on 04/06/2016.
//

#pragma once


#include <AL/al.h>
#include "Buffer.h"

namespace audio {

    class Source {
    private:
        ALuint id_;
        audio::Buffer buffer_;
    public:
        Source(ALuint sourceID, const audio::Buffer &buffer, bool relative = false);

        Source() {}

        void setPosition(float posX, float posY, float posZ);

        void play();

        void pause();

        void stop();

        void setPitch(float pitch);


        ALuint getId() const;

        void release();
    };
}