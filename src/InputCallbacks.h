#pragma once

#include "gfx/MazeCamera.h"

// Classe statica contenente le callback Glut relative all'input del giocatore
class InputCallbacks {
    // GlutCallbacks può vedere i membri privati di questa classe
    friend class GlutCallbacks;
private:
    // Velocità di spostamento al millisecondo
    static const float TRANSLATION_SPEED;
    // Velocità di rotazione
    static const float ROTATION_SPEED;

    static gfx::MazeCamera camera_;
    static int viewportWidth_;
    static int viewportHeight_;
    // Contiene true per ogni tasto della tastiera che è correntemente premuto dal giocatore (solo tasti ASCII)
    static bool key_[256];
    // Contiene true se il corrispondente tasto freccia è premuto dal giocatore
    static bool specialKey_[4];
    // True se il gioco non è in pausa ed è possibile effettuare movimenti
    static bool movement_;
    // Pressione dei tasti mouse
    static bool mouseLeftDown_;
    static bool mouseRightDown_;
    // Tempo corrente in millisecondi (epoch time)
    static int currTime_;
public:
    // Callback per glutKeyboardFunc, aggiorna l'array key_ in base ai tasti che vengono premuti
    static void keyboard(unsigned char key, int x, int y);
    // Callback per glutKeyboardUpFunc, aggiorna l'array key_ in base ai tasti che vengono rilasciati
    static void keyboardUp(unsigned char key, int x, int y);
    // Callback per glutSpecialFunc, riservata ai tasti freccia che vengono premuti
    static void keyboardSpecial(int key, int x, int y);
    // Callback per glutSpecialUpFunc, riservata ai tasti freccia che vengono rilasciati
    static void keyboardSpecialUp(int key, int x, int y);
    // Callback per glutTimerFunc, viene eseguita ogni 16ms (circa 60 volte al secondo) e,
    // in base ai tasti che sono premuti in quel momento, si occupa di muovere il giocatore e di
    // aggiornare lo stato di gioco
    static void timer(int value);
    // Callback per glutMouseFunc, registra la pressione e il rilascio dei tasti destro e sinistro del mouse
    static void mouse(int button, int state, int x, int y);
    // Callback per glutMouseMotionFunc, si occupa di ruotare la visuale in base al movimento del mouse
    static void mouseMotion(int x, int y);
};


