#include <fstream>
#include <algorithm>
#include "Settings.h"

const std::string game::Settings::settingsFilePath_ = "res/config.cfg";

const std::map<std::string, int> game::Settings::defaults_ = {
        {"MULTISAMPLING",   4},
        {"DRAW_DISTANCE",   15},
        {"MAZE_SIZE_X",     65},
        {"MAZE_SIZE_Y",     65},
        {"MAZE_RANDOMNESS", 25},
        {"ALARM_COUNT",     5},
        {"DEAD_ENDS",       1},
        {"ENABLE_FLIGHT",   0},
        {"DISABLE_LIGHT_ATTENUATION", 0}
};

const std::map<std::string, int> game::Settings::minimums_ = {
        {"MULTISAMPLING",   0},
        {"DRAW_DISTANCE",   1},
        {"MAZE_SIZE_X",     5},
        {"MAZE_SIZE_Y",     5},
        {"MAZE_RANDOMNESS", 0},
        {"ALARM_COUNT",     1},
        {"DEAD_ENDS",       0},
        {"ENABLE_FLIGHT",   0},
        {"DISABLE_LIGHT_ATTENUATION", 0}
};

const std::map<std::string, int> game::Settings::maximums_ = {
        {"MULTISAMPLING",   16},
        {"MAZE_RANDOMNESS", 100},
        {"DEAD_ENDS",       1},
        {"ENABLE_FLIGHT",   1},
        {"DISABLE_LIGHT_ATTENUATION", 1}
};

game::Settings::Settings() {
    std::ifstream cfg;
    cfg.open(settingsFilePath_);

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
            } catch (...) {
                value = -1;
            }

            if (defaults_.find(name) != defaults_.end()) { // Se il nome dell'impostazione è valido

                if (minimums_.find(name) != minimums_.end() && value < minimums_.at(name) ||
                        maximums_.find(name) != maximums_.end() && value > maximums_.at(name)) {
                    // Il valore dell'impostazione è troppo alto o basso: viene usato quello predefinito
                    value = defaults_.at(name);
                }

                settingsMap_[name] = value;
            }

        }

    }

    cfg.close();
}

game::Settings& game::Settings::getInstance() {
    // instance viene inizializzato solo alla prima invocazione, dopo viene riutilizzato
    // Alla fine dell'esecuzione del programma viene distrutta automaticamente
    static game::Settings instance;
    return instance;
}

int game::Settings::operator[](const std::string &name) const {
    // Se l'impostazione è stata letta correttamente, ne viene restituito il valore
    if (settingsMap_.find(name) != settingsMap_.end()) return settingsMap_.at(name);
    // Altrimenti usa quello di default
    if (defaults_.find(name) != defaults_.end()) return defaults_.at(name);

    // Se il nome dell'impostazione è errato, ritorna -1
    return -1;
}