//
// Created by Admin on 03/06/2016.
//

#include <fstream>
#include <algorithm>
#include "Settings.h"

const std::string Settings::settingsFilePath = "res/config.cfg";

const std::map<std::string, int> Settings::defaults = {
        {"MULTISAMPLING",   4},
        {"DRAW_DISTANCE",   15},
        {"MAZE_SIZE_X",     65},
        {"MAZE_SIZE_Y",     65},
        {"MAZE_RANDOMNESS", 25},
        {"ALARM_COUNT",     5},
        {"DEAD_ENDS",       1},
        {"ENABLE_FLIGHT",   0}
};

const std::map<std::string, int> Settings::minimums = {
        {"MULTISAMPLING",   0},
        {"DRAW_DISTANCE",   1},
        {"MAZE_SIZE_X",     5},
        {"MAZE_SIZE_Y",     5},
        {"MAZE_RANDOMNESS", 0},
        {"ALARM_COUNT",     1},
        {"DEAD_ENDS",       0},
        {"ENABLE_FLIGHT",   0}
};

const std::map<std::string, int> Settings::maximums = {
        {"MULTISAMPLING",   16},
        {"MAZE_RANDOMNESS", 100},
        {"DEAD_ENDS",       1},
        {"ENABLE_FLIGHT",   1}
};

Settings::Settings() {
    std::ifstream cfg;
    cfg.open(settingsFilePath);

    std::string line;
    while (std::getline(cfg, line, '\n')) { // Legge il file linea per linea

        // Se è presente il carattere windows \r lo elimina
        if (line.length() > 0 && line[line.length() - 1] == '\r')
            line.erase(line.length() - 1);

        // Rimuove tutti gli spazi dalla linea
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // Se la linea è vuota o è un commento (inizia con #) viene saltata
        if (line.length() == 0 || line[0] == '#') continue;

        auto equal = line.find('='); // Posizione del segno uguale nella stringa (NOME = valore)

        if (equal != std::string::npos) { // Se c'è il segno '=', l'impostazione è ben formata
            std::string name = line.substr(0, equal);
            int value;

            try { // Prova a convertire il valore in intero. Se non ci riesce, gli viene assegnato -1
                value = stoi(line.substr(equal + 1));
            } catch (const std::exception &ex) {
                value = -1;
            }

            if (defaults.find(name) != defaults.end()) { // Se il nome dell'impostazione è valido

                if (minimums.find(name) != minimums.end() && value < minimums.at(name) ||
                        maximums.find(name) != maximums.end() && value > maximums.at(name)) {
                    // Il valore dell'impostazione è troppo alto o basso: viene usato quello predefinito
                    value = defaults.at(name);
                }

                settingsMap[name] = value;
            }

        }

    }

    cfg.close();
}

Settings& Settings::getInstance() {
    // instance viene inizializzato solo alla prima invocazione, dopo viene riutilizzato
    // Alla fine dell'esecuzione del programma viene distrutta automaticamente
    static Settings instance;
    return instance;
}

int Settings::operator[](std::string name) const {
    // Se l'impostazione è stata letta correttamente, ne viene restituito il valore
    if (settingsMap.find(name) != settingsMap.end()) return settingsMap.at(name);
    // Altrimenti usa quello di default
    if (defaults.find(name) != defaults.end()) return defaults.at(name);

    // Se il nome dell'impostazione è errato, ritorna -1
    return -1;
}