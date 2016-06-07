//
// Created by Admin on 04/06/2016.
//

#include <map>
#include <AL/alut.h>
#include "Manager.h"

const std::vector<std::string> audio::Manager::audioFiles_ = {
        "res/audio/alarm0.wav",
        "res/audio/alarm1.wav",
        "res/audio/alarm2.wav",
        "res/audio/alarm3.wav",
        "res/audio/alarm4.wav"
};

audio::Manager::Manager() {
    for(auto it = audioFiles_.begin(); it != audioFiles_.end(); ++it){
        alutInit(nullptr, nullptr);
        ALuint id;
        alGenBuffers(1, &id);
        id = alutCreateBufferFromFile(it->c_str());
        audioBuffers_.push_back(audio::Buffer(id));
    }
}

void audio::Manager::bindSources(std::shared_ptr<game::Maze> maze) {
    for(int i = 0; i < maze->getAlarmCount(); ++i){
        game::Coordinates alm = maze->getAlarm(i);
        ALuint sid;
        alGenSources(1, &sid);
        audio::Source almSound(sid, audioBuffers_[i % audioBuffers_.size()]);
        almSound.setPitch(1.0f + ((i - (i % audioBuffers_.size())) / audioBuffers_.size() * 0.3f));
        almSound.setPosition(alm.first * 0.4f - 0.4f, 0.0f, alm.second * -0.4f + 0.4f);
        alarmSounds_.insert(std::make_pair(alm, almSound));
    }
}

audio::Source audio::Manager::operator[](const game::Coordinates &pos) {
    return alarmSounds_.at(pos);
}

void audio::Manager::playAll() {
    for (auto it = alarmSounds_.begin(); it != alarmSounds_.end(); ++it) {
        it->second.play();
    }
}

void audio::Manager::pauseAll() {
    for (auto it = alarmSounds_.begin(); it != alarmSounds_.end(); ++it) {
        it->second.pause();
    }
}

void audio::Manager::releaseSounds(){
    for (auto it = alarmSounds_.begin(); it != alarmSounds_.end(); ++it) {
        it->second.release();
    }
    alarmSounds_.clear();
}

audio::Manager::~Manager(){
    for(auto it = audioBuffers_.begin(); it != audioBuffers_.end(); ++it){
        it->release();
    }
}

void audio::Manager::eraseSound(const game::Coordinates &pos) {
    alarmSounds_[pos].release();
    alarmSounds_.erase(pos);
    alutExit();
}
