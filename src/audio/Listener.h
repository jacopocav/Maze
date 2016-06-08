#pragma once

namespace audio {
    // Classe statica contenente le funzioni che permettono di controllare l'ascoltatore audio
    class Listener {
    public:
        // Imposta la direzione dell'ascoltatore
        // I primi tre parametri rappresentano il vettore at, ovvero la direzione di ascolto
        // I restanti tre rappresentano il vettore up, ovvero la direzione dell'"alto" relativamente all'ascoltatore.
        // up dev'essere ortogonale ad at e serve a determinare da che parte sono l'orecchio sx e quello dx
        // (ad es., se l'ascoltatore fosse a testa in giù, il vettore up punterebbe verso il basso).
        static void setOrientation(float atx, float aty, float atz, float upx, float upy, float upz);

        // Imposta la posizione dell'ascoltatore
        static void setPosition(float x, float y, float z);
    };
}
