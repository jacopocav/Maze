//
// Created by Admin on 26/05/2016.
//

#pragma once


#include <GL/glut.h>
#include <string>
#include <map>
namespace gfx {
    // TODO commentare classe
    class Textures {
    private:
        static std::map<std::string, int> textureTable_;
        static GLuint *textures_;
        static int textureCount_;
    public:

        static void initTextures(int texCount);

        static void readFromBMP(const std::string &path, int textureIndex, const std::string &name);

        static void useTexture(const std::string &name);

        static void resetTextures();
    };

}