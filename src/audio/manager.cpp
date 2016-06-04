//
// Created by Admin on 04/06/2016.
//

#include <map>
#include <AL/alut.h>
#include "manager.h"
#include "source.h"

const std::vector<std::string> audio::manager::audioFiles = {
        "res/audio/alarm0.wav",
        "res/audio/alarm1.wav",
        "res/audio/alarm2.wav",
        "res/audio/alarm3.wav",
        "res/audio/alarm4.wav"
};

std::vector<audio::buffer> audio::manager::Init() {
    std::vector<audio::buffer> bufs;
    for(auto it = audioFiles.begin(); it != audioFiles.end(); ++it){
        ALuint id;
        alGenSources(1, &id);
        id = alutCreateBufferFromFile(it->c_str());
        bufs.push_back(audio::buffer(id));
    }
    return bufs;
}

std::map<Coordinates, audio::source> audio::manager::BindSourcesToAlarms(Maze *maze, const std::vector<audio::buffer> &bufs) {
    std::map<Coordinates, audio::source> alarms;
    for(int i = 0; i < maze->getAlarmCount(); ++i){
        Coordinates alm = maze->getAlarm(i);
        ALuint sid;
        alGenSources(1, &sid);
        audio::source almSound(sid, bufs[i % bufs.size()]);
        almSound.setPitch(1.0f + ((i - (i % bufs.size())) / bufs.size() * 0.3f));
        almSound.setPosition(alm.first * 0.4f - 0.4f, 0.0f, alm.second * -0.4f + 0.4f);
        alarms.insert(std::make_pair(alm, almSound));
    }
    return alarms;
}