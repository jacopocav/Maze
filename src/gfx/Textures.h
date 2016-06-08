#pragma once

#include <string>
#include <map>
#include <GL/glut.h>

namespace gfx {
    // Classe statica che gestisce le texture del gioco
    class Textures {
    private:
        // Mappa che associa un nome agli indici di ogni texture (indici della loro posizione in textures_)
        static std::map<std::string, int> textureTable_;
        // Array di identificatori di texture
        static GLuint *textures_;
        // Numero di texture aperte
        static int textureCount_;
        // Usato nel caricamento di texture per determinare l'indice in textures_ della nuova texture da caricare
        static int currTextureIndex_;
    public:
        // Inizializza un certo numero di texture
        static void initTextures(int texCount);
        // Legge una texture da file .bmp e la carica associandole un nome
        static void readFromBMP(const std::string &path, const std::string &name);
        // Usa la texture con il nome passato per parametro
        static void useTexture(const std::string &name);
        // Rilascia le texture dalla memoria
        static void resetTextures();
    };

}