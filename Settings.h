//
// Created by Admin on 03/06/2016.
//

#pragma once


#include <string>
#include <map>

class Settings {
private:
    static const std::string settingsFilePath;
    static const std::map<std::string, int> defaults;
    static const std::map<std::string, int> minimums;
    static const std::map<std::string, int> maximums;
    std::map<std::string, int> settingsMap;
    Settings();
public:
    static Settings& getInstance();
    int getSettingValue(std::string name) const;
    int operator[](std::string name) const;

    Settings(Settings const& s) = delete;
    Settings& operator=(Settings const& e) = delete;
};
