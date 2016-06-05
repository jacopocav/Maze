//
// Created by Admin on 26/05/2016.
//

#pragma once


#include <GL/glut.h>
#include <string>
#include <map>
namespace gfx {
    class Textures {
    private:
        static std::map<std::string, int> textureTable_;
        static GLuint *textures_;
        static int textureCount_;
    public:

        static void initTextures(int texCount);

        static void readFromBMP(std::string path, int textureIndex, std::string name);

        static void bindTexture(std::string name);

        static void resetTextures();
    };

}