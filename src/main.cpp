// Maze, di Jacopo Cavallarin (1131015)
//
// Progetto per il corso di Sistemi Multimediali, AA 2015/2016.
// CdL Magistrale in Informatica - Dipartimento di Matematica - Università degli Studi di Padova
//
// -- SCOPO DEL GIOCO --
// Attraversare il labirinto e disattivare gli allarmi sparsi al suo interno entro un certo tempo limite.
// Gli allarmi emettono un suono, che fornisce un indizio sulla loro posizione.
// Per disattivare un allarme, basta passarci attraverso.
// Ogni volta che ne viene disattivato uno, il tempo limite può aumentare se gli allarmi restanti sono
// particolarmente distanti.
// La partita finisce una volta disattivati tutti gli allarmi (vittoria)
// o se il tempo limite è scaduto (sconfitta).
//
// -- CONTROLLI --
//                      SPAZIO - Inizia gioco e attiva/disattiva pausa
//                           R - Abbandona partita corrente e comincia una nuova (è considerata una sconfitta)
// NB: I seguenti comandi funzionano solo quando il gioco non è in pausa
//                         W,S - Spostamento avanti/indietro
//                         A,D - Spostamento laterale sinistra/destra
//                       Mouse - Puntamento visuale
//    Freccia SINISTRA, DESTRA - Ruota visuale a sx/dx
//     Clic Destro, Freccia SU - Vola in alto (se volo abilitato)
//  Clic Sinistro, Freccia GIU - Vola in basso (se volo abilitato)
//
// -- IMPOSTAZIONI --
// Dentro la cartella res è presente il file config.cfg, che contiene alcune impostazioni modificabili dall'utente.
// La descrizione di ogni impostazione è contenuta nel file stesso.


#include <GL/glut.h>
#include <iostream>

#include "GlutCallbacks.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    GlutCallbacks::init();
    return 0;
}