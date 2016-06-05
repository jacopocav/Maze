//
// Created by Admin on 26/05/2016.
//

#include <fstream>
#include <iostream>
#include "Textures.h"

GLuint *gfx::Textures::textures_;
int gfx::Textures::textureCount_;
std::map<std::string, int> gfx::Textures::textureTable_;

void gfx::Textures::initTextures(int texCount) {
    textures_ = new GLuint[texCount];
    glGenTextures(texCount, textures_);
    textureCount_ = texCount;
}

void gfx::Textures::readFromBMP(std::string path, int textureIndex, std::string name = "") {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned dataPos;     // Position in the file where the actual data begins
    unsigned width, height;
    unsigned imageSize;   // = width*height*3
// Actual RGB data
    GLubyte *data;

    // Open the file
    FILE *file = fopen(path.c_str(), "rb");
    if (!file) {
        std::cerr << "Image could not be opened\n";
        return;
    }

    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        std::cerr << "Not a correct BMP file\n";
        return;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        std::cerr << "Not a correct BMP file\n";
        return;
    }

    dataPos = *(unsigned *) &(header[0x0A]);
    imageSize = *(unsigned *) &(header[0x22]);
    width = *(unsigned *) &(header[0x12]);
    height = *(unsigned *) &(header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) dataPos = 54; // The BMP header is done that way

    // Create a buffer_
    data = new GLubyte[imageSize];

    // Read the actual data from the file into the buffer_
    fread(data, 1, imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    for (int i = 0; i < imageSize; i += 3) {
        auto tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    if (textureIndex < textureCount_) {
        textureTable_[name] = textureIndex;

        glBindTexture(GL_TEXTURE_2D, textures_[textureIndex]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, height, width, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    delete data;
}

void gfx::Textures::bindTexture(std::string name) {
    if (name == "0") {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (textureTable_.find(name) != textureTable_.end()) {
        glBindTexture(GL_TEXTURE_2D, textures_[textureTable_[name]]);
    }
}

void gfx::Textures::resetTextures() {
    glDeleteTextures(textureCount_, textures_);
    delete textures_;
    textureTable_.clear();
}