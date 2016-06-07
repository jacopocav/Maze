//
// Created by Admin on 04/06/2016.
//

#pragma once

namespace audio {
    // TODO commentare classe
    class Listener {
    public:
        static void setOrientation(float atx, float aty, float atz, float upx, float upy, float upz);

        static void setPosition(float x, float y, float z);
    };
}
