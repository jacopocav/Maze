#include <fstream>
#include <iostream>
#include "Textures.h"

GLuint *gfx::Textures::textures_;
int gfx::Textures::textureCount_;
std::map<std::string, int> gfx::Textures::textureTable_;
int gfx::Textures::currTextureIndex_ = 0;

void gfx::Textures::initTextures(int texCount) {
    textures_ = new GLuint[texCount];
    glGenTextures(texCount, textures_);
    textureCount_ = texCount;
}

void gfx::Textures::readFromBMP(const std::string &path, const std::string &name) {
    unsigned char header[54]; // Header del BMP, sempre lungo 54 byte
    unsigned width, height; // Larghezza, altezza immagine
    unsigned imageSize;   // Dimensione immagine in byte= width*height*3

    GLubyte *data; // Conterrà i byte dell'immagine

    std::ifstream image;
    image.open(path, std::ios::binary);

    image.read(reinterpret_cast<char *>(header), 54); // Lettura dell'header

    if (header[0] != 'B' || header[1] != 'M') {
        throw std::runtime_error("Not a correct BMP file\n");
    }

    imageSize = *reinterpret_cast<unsigned *>(&(header[0x22]));
    width = *reinterpret_cast<unsigned *>(&(header[0x12]));
    height = *reinterpret_cast<unsigned *>(&(header[0x16]));

    // Alcuni BMP possono avere informazioni sbagliate sulle dimensioni dell'immagine
    if (imageSize == 0) imageSize = width * height * 3; // Deduce dimensione dell'immagine

    data = new GLubyte[imageSize];

    // Copia l'immagine in data
    image.read(reinterpret_cast<char *>(data), imageSize);

    // Ora il file non serve più
    image.close();

    // Le BMP contengono i colori in ordine BGR, quindi vanno riordinati in RGB
    for (int i = 0; i < imageSize; i += 3) {
        auto tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    if (currTextureIndex_ < textureCount_) { // Memorizza l'immagine nella texture
        textureTable_[name] = currTextureIndex_;

        glBindTexture(GL_TEXTURE_2D, textures_[currTextureIndex_]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, height, width, GL_RGB, GL_UNSIGNED_BYTE, data);
        currTextureIndex_++;
    }

    delete data; // Una volta memorizzata nella texture, l'immagine non serve più
}

void gfx::Textures::useTexture(const std::string &name) {
    if (name != "0" && textureTable_.find(name) != textureTable_.end()) {
        glBindTexture(GL_TEXTURE_2D, textures_[textureTable_[name]]);
    } else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void gfx::Textures::resetTextures() {
    glDeleteTextures(textureCount_, textures_);
    delete textures_;
    textureTable_.clear();
    currTextureIndex_ = 0;
}