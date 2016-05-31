//
// Created by Admin on 30/05/2016.
//

#pragma once


#include <map>
#include <AL/alut.h>

class AudioFunctions {
private:
    static ALuint *sources;
    static ALuint *buffers;
    static int sourceCount;
    static std::map<std::string, int> sourceTable;

public:
    static void InitSources(int srcCount);
    static void LoadSourceFromFile(std::string path, int sourceIndex, std::string name, bool looping,
                                      float pitch);
    static void RemoveSource(std::string name);
    static void PlaySource(std::string name);
    static void PauseSource(std::string name);

    static void PlayAll();
    static void PauseAll();

    static void SetSourcePosition(std::string name, float x, float y, float z);
    static void SetListenerPosition(float x, float y, float z);
    static void SetListenerOrientation(float atx, float aty, float atz, float upx, float upy, float upz);

};
