#include <GL/glut.h>
#include <iostream>
#include <AL/alut.h>

#include "BigMess.h"

using namespace std;


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    alutInit(&argc, argv);
    BigMess::Init();
    alutExit();
    return 0;
}

/*#include <iostream>
#include <AL/alut.h>
#include <map>

#include "audio/buffer_.h"
#include "audio/Source.h"
#include "audio/Listener.h"
#include "audio/Manager.h"
#include "game/MazeGenerator.h"

using namespace std;


int main(int argc, char **argv) {
    alutInit(&argc, argv);
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

    auto bufs = audio::Manager::init();
    Maze* m = MazeGenerator::generateMaze(65, 65);
    MazeGenerator::addAlarmsToMaze(m, 5);
    std::map<Coordinates, audio::Source> almMaps = audio::Manager::bindSourcesToAlarms(m, bufs);

    for(auto it = almMaps.begin(); it != almMaps.end(); ++it){
        it->second.play();
    }

    for(int i = 0; i < 100; ++i){
        alutSleep(0.1f);
    }

    for(auto it = almMaps.begin(); it != almMaps.end(); ++it){
        it->second.release();
    }

    for(auto it = bufs.begin(); it != bufs.end(); ++it){
        it->release();
    }

    alutExit();
    return 0;
}*/

