//
// Created by Admin on 04/06/2016.
//

#pragma once

#include <string>
#include <vector>
#include <AL/al.h>
#include <memory>
#include "Buffer.h"
#include "../game/Maze.h"
#include "Source.h"

namespace audio {
    // TODO commentare classe
    class Manager {
    private:
        static const std::vector<std::string> audioFiles_;
        std::vector<audio::Buffer> audioBuffers_;
        std::map<game::Coordinates, audio::Source> alarmSounds_;
    public:
        Manager();
        void bindSources(std::shared_ptr<game::Maze> maze);
        audio::Source operator[](const game::Coordinates &pos);
        void playAll();
        void pauseAll();
        void releaseSounds();
        void eraseSound(const game::Coordinates &pos);
        ~Manager();
    };
}
