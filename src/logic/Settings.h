//
// Created by Admin on 03/06/2016.
//

#pragma once


#include <string>
#include <map>

class Settings {
private:
    // Percorso relativo del file di configurazione
    static const std::string settingsFilePath;
    // Valori di default delle impostazioni
    static const std::map<std::string, int> defaults;
    // Valori minimi di ogni impostazione (ove previsti)
    static const std::map<std::string, int> minimums;
    // Valori massimi di ogni impostazione (ove previsti)
    static const std::map<std::string, int> maximums;

    // Valori delle impostazioni lette da file
    std::map<std::string, int> settingsMap;
    Settings();
public:
    // Ritorna l'unica istanza della classe
    static Settings& getInstance();

    // Ritorna il valore di una determinata impostazione (se non esiste, ritorna -1)
    int operator[](std::string name) const;

    // Per impedire la copia dell'oggetto singleton
    Settings(Settings const& s) = delete;
    Settings& operator=(Settings const& e) = delete;
};
