cmake_minimum_required(VERSION 3.5)
project(Maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES src/main.cpp src/gfx/Camera.h src/gfx/Camera.cpp src/logic/MazeGenerator.cpp src/logic/MazeGenerator.h src/logic/Maze.cpp src/logic/Maze.h src/gfx/BigMess.cpp
        src/gfx/BigMess.h src/gfx/MazeCamera.cpp src/gfx/MazeCamera.h src/gfx/Textures.cpp src/gfx/Textures.h src/gfx/Drawing.cpp
        src/gfx/Drawing.h src/logic/Settings.cpp src/logic/Settings.h src/audio/source.cpp src/audio/source.h src/audio/buffer.cpp src/audio/buffer.h src/audio/listener.cpp src/audio/listener.h src/audio/manager.cpp src/audio/manager.h )
add_executable(Maze ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} "C:/freeglut/include" "C:/Program Files (x86)/OpenAL 1.1 SDK/include" "C:/freealut/include/")
target_link_libraries(Maze ${OPENGL_LIBRARIES} "C:/freeglut/lib/libfreeglut.a" "C:/Program Files (x86)/OpenAL 1.1 SDK/libs/Win32/OpenAL32.lib" "C:/freealut/lib/libalut.dll.a" )

file(COPY res/ DESTINATION res)