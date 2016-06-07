//
// Created by Admin on 04/06/2016.
//

#pragma once


#include <AL/al.h>
#include <string>

namespace audio {
    // Classe che racchiude le informazioni di un buffer (file) audio aperto precedentemente in OpenAL
    class Buffer {
    private:
        // "Nome" del buffer. Lo identifica ed è necessario per effettuare qualsiasi operazione su di esso
        ALuint id_;
    public:
        // Il costruttore non crea il buffer: dev'essere stato creato precedentemente alla costruzione.
        // Questo perché C++ può creare implicitamente copie dell'oggetto, e inserire l'apertura del buffer nel
        // costruttore comporterebbe l'apertura di molti buffer identici.
        Buffer(ALuint bufferID);

        Buffer() {};

        ALuint getID() const;

        // Elimina il buffer associato all'oggetto. Non viene fatto nel distruttore perché C++
        // lo può distruggere implicitamente se passato come parametro.
        void release();

    };
}
