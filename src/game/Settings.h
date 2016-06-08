#pragma once


#include <string>
#include <map>

namespace game {
    // Classe singleton che gestisce le impostazioni lette da file
    class Settings {
    private:
        // Percorso relativo del file di configurazione
        static const std::string settingsFilePath_;
        // Valori di default delle impostazioni
        static const std::map<std::string, int> defaults_;
        // Valori minimi di ogni impostazione (ove previsti)
        static const std::map<std::string, int> minimums_;
        // Valori massimi di ogni impostazione (ove previsti)
        static const std::map<std::string, int> maximums_;

        // Valori delle impostazioni lette da file
        std::map<std::string, int> settingsMap_;

        Settings();

    public:
        // Ritorna l'unica istanza della classe
        static Settings &getInstance();

        // Ritorna il valore di una determinata impostazione (se non esiste, ritorna -1)
        int operator[](const std::string &name) const;

        // Per impedire la copia dell'oggetto singleton
        Settings(const Settings &s) = delete;

        Settings &operator=(const Settings &e) = delete;
    };
}