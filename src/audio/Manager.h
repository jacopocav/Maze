#pragma once

#include <string>
#include <vector>
#include <memory>

#include <AL/al.h>

#include "Buffer.h"
#include "Source.h"
#include "../game/Maze.h"


namespace audio {
    // Classe che si occupa di gestire l'audio del gioco
    class Manager {
    private:
        // Lista dei file audio da caricare. Se gli allarmi sono in numero maggiore rispetto ai file caricati,
        // vengono utilizzati più volte, aumentandone il pitch a ogni riutilizzo.
        static const std::vector<std::string> audioFiles_;
        // Lista dei buffer audio aperti
        std::vector<audio::Buffer> audioBuffers_;
        // Mappa che associa ad ogni posizione di allarme la relativa sorgente audio
        std::map<game::Coordinates, audio::Source> alarmSounds_;
    public:
        // Inizializza OpenAL e carica i file audio nei buffer
        Manager();
        // Dato il labirinto, crea una sorgente per ogni allarme e la mappa alla sua posizione nel labirinto
        void bindSources(std::shared_ptr<game::Maze> maze);
        // Ritorna la sorgente audio corrispondente all'allarme in posizione pos (se presente)
        audio::Source operator[](const game::Coordinates &pos);
        // Avvia la riproduzione in loop di tutte le sorgenti
        void playAll();
        // Mette in pausa tutte le sorgenti
        void pauseAll();
        // Rimuove tutte le sorgenti (ma lascia aperti i buffer)
        void releaseSounds();
        // Rimuove la sorgente corrispondente alla posizione pos (se presente)
        void eraseSound(const game::Coordinates &pos);
        // Elimina tutte le sorgenti ancora aperte, tutti i buffer e chiude OpenAL
        ~Manager();
    };
}
