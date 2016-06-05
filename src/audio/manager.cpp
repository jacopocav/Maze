//
// Created by Admin on 04/06/2016.
//

#include <map>
#include <AL/alut.h>
#include "Manager.h"
#include "Source.h"

const std::vector<std::string> audio::Manager::audioFiles_ = {
        "res/audio/alarm0.wav",
        "res/audio/alarm1.wav",
        "res/audio/alarm2.wav",
        "res/audio/alarm3.wav",
        "res/audio/alarm4.wav"
};

std::vector<audio::Buffer> audio::Manager::init() {
    std::vector<audio::Buffer> bufs;
    for(auto it = audioFiles_.begin(); it != audioFiles_.end(); ++it){
        ALuint id;
        alGenSources(1, &id);
        id = alutCreateBufferFromFile(it->c_str());
        bufs.push_back(audio::Buffer(id));
    }
    return bufs;
}

std::map<game::Coordinates, audio::Source> audio::Manager::bindSourcesToAlarms(game::Maze *maze,
                                                                         const std::vector<audio::Buffer> &bufs) {
    std::map<game::Coordinates, audio::Source> alarms;
    for(int i = 0; i < maze->getAlarmCount(); ++i){
        game::Coordinates alm = maze->getAlarm(i);
        ALuint sid;
        alGenSources(1, &sid);
        audio::Source almSound(sid, bufs[i % bufs.size()]);
        almSound.setPitch(1.0f + ((i - (i % bufs.size())) / bufs.size() * 0.3f));
        almSound.setPosition(alm.first * 0.4f - 0.4f, 0.0f, alm.second * -0.4f + 0.4f);
        alarms.insert(std::make_pair(alm, almSound));
    }
    return alarms;
}