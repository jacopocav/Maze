cmake_minimum_required(VERSION 3.5)
project(Maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES src/main.cpp src/gfx/Camera.h src/gfx/Camera.cpp src/game/MazeGenerator.cpp src/game/MazeGenerator.h src/game/Maze.cpp src/game/Maze.h src/BigMess.cpp
        src/BigMess.h src/gfx/MazeCamera.cpp src/gfx/MazeCamera.h src/gfx/Textures.cpp src/gfx/Textures.h src/gfx/Drawing.cpp
        src/gfx/Drawing.h src/game/Settings.cpp src/game/Settings.h src/audio/Source.cpp src/audio/Source.h src/audio/Buffer.cpp src/audio/Buffer.h src/audio/Listener.cpp src/audio/Listener.h src/audio/Manager.cpp src/audio/Manager.h)
add_executable(Maze ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} "C:/freeglut/include" "C:/Program Files (x86)/OpenAL 1.1 SDK/include" "C:/freealut/include/")
target_link_libraries(Maze ${OPENGL_LIBRARIES} "C:/freeglut/lib/libfreeglut.a" "C:/Program Files (x86)/OpenAL 1.1 SDK/libs/Win32/OpenAL32.lib" "C:/freealut/lib/libalut.dll.a" )

file(COPY res/ DESTINATION res)