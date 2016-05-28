//
// Created by Admin on 26/05/2016.
//

#pragma once


#include <GL/glut.h>
#include <string>
#include <map>

class TextureUtils {
private:
    static std::map<std::string, int> textureTable;
    static int textureCount;
public:
    static GLuint *textures;
    static void InitializeTextures(int texCount);

    static void LoadBMPTexture(std::string path);

    static void ReadFromBMP(std::string path, int textureIndex, std::string name);

    static void BindTexture(int textureIndex);

    static void BindTexture(std::string name);

    static void ResetTextures();
};

