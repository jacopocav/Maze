//
// Created by Admin on 04/06/2016.
//

#pragma once

#include <string>
#include <vector>
#include <AL/al.h>
#include "buffer.h"
#include "../logic/Maze.h"
#include "source.h"

namespace audio {
    class manager {
    private:
        static const std::vector<std::string> audioFiles;
    public:
        static std::vector<audio::buffer> Init();
        static std::map<Coordinates, audio::source> BindSourcesToAlarms(Maze *maze, const std::vector<audio::buffer> &bufs);
    };
}