//
// Created by Admin on 04/06/2016.
//

#pragma once

namespace audio {
    class listener {
    public:
        static void SetOrientation(float atx, float aty, float atz, float upx, float upy, float upz);

        static void SetPosition(float x, float y, float z);
    };
}
