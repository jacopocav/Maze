//
// Created by Admin on 26/05/2016.
//

#pragma once


#include <GL/glut.h>
#include <string>
#include <map>

class TextureFunctions {
private:
    static std::map<std::string, int> textureTable;
    static GLuint *textures;
    static int textureCount;
public:

    static void InitTextures(int texCount);

    static void ReadFromBMP(std::string path, int textureIndex, std::string name);

    static void BindTexture(int textureIndex);

    static void BindTexture(std::string name);

    static void ResetTextures();
};

