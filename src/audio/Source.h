#pragma once


#include <AL/al.h>
#include "Buffer.h"

namespace audio {
    // Classe che contiene le informazioni di una sorgente audio OpenAL
    class Source {
    private:
        // ID univoco della sorgente
        ALuint id_;
        // Buffer associato alla sorgente
        audio::Buffer buffer_;
    public:
        // Non apre una nuova sorgente, l'id passato per parametro deve corrispondere ad una sorgente già aperta
        // Vengono impostati alcuni parametri della sorgente, come il looping e il rolloff
        Source(ALuint sourceID, const audio::Buffer &buffer);

        Source() = default;

        // Imposta la posizione della sorgente (assoluta, non relativa all'ascoltatore)
        void setPosition(float posX, float posY, float posZ);

        void play();

        void pause();

        void stop();

        // Imposta il pitch della sorgente
        void setPitch(float pitch);

        ALuint getId() const;

        // Elimina la sorgente (NON il buffer associato). Le ragioni per cui release non viene effettuata
        // nel distruttore sono le stesse della classe Buffer
        void release();
    };
}