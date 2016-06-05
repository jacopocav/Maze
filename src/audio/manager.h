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
    public:
        static std::vector<audio::Buffer> init();
        static std::map<game::Coordinates, audio::Source> bindSourcesToAlarms(game::Maze *maze,
                                                                        const std::vector<audio::Buffer> &bufs);
    };
}