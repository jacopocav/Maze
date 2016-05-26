//
// Created by Admin on 26/05/2016.
//

#include <fstream>
#include "TextureUtils.h"

GLubyte *TextureUtils::ReadFromFile(std::string path) {
    std::ifstream ifs;
    ifs.open(path, std::ifstream::binary);

    ifs.seekg(54, std::ifstream::beg);

    GLubyte* texture = new GLubyte[512*512*3];

    ifs.read(reinterpret_cast<char*>(texture), 512*512*3);

    return texture;
}