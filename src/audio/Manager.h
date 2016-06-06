//
// Created by Admin on 04/06/2016.
//

#pragma once

#include <string>
#include <vector>
#include <AL/al.h>
#include "Buffer.h"
#include "../game/Maze.h"
#include "Source.h"

namespace audio {
    class Manager {
    private:
        static const std::vector<std::string> audioFiles_;
        std::vector<audio::Buffer> audioBuffers_;
        std::map<game::Coordinates, audio::Source> alarmSounds_;
    public:
        Manager();
        void bindSources(game::Maze *maze);
        audio::Source operator[](game::Coordinates);
        void playAll();
        void pauseAll();
        void releaseSounds();
        void eraseSound(game::Coordinates pos);
        ~Manager();
    };
}
