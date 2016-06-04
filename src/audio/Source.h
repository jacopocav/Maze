//
// Created by Admin on 04/06/2016.
//

#pragma once


#include <AL/al.h>
#include "buffer.h"

namespace audio {

    class source {
    private:
        ALuint id;
        audio::buffer buffer;
        float x, y, z;
    public:
        source(ALuint sourceID, const audio::buffer &buf);

        void setPosition(float posX, float posY, float posZ);

        void play();

        void pause();

        void stop();

        void setPitch(float pitch);


        ALuint getId() const;

        void release();

        /*~source();
        source(source&& other);
        source& operator=(source&& other);*/
    };
}