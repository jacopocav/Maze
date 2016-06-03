cmake_minimum_required(VERSION 3.5)
project(Maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp Camera.h Camera.cpp MazeGenerator.cpp MazeGenerator.h Maze.cpp Maze.h GlutFunctions.cpp
        GlutFunctions.h MazeCamera.cpp MazeCamera.h TextureFunctions.cpp TextureFunctions.h DrawingFunctions.cpp
        DrawingFunctions.h AudioFunctions.cpp AudioFunctions.h Settings.cpp Settings.h)
add_executable(Maze WIN32 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} "C:/freeglut/include" "C:/Program Files (x86)/OpenAL 1.1 SDK/include" "C:/freealut/include/")
target_link_libraries(Maze ${OPENGL_LIBRARIES} "C:/freeglut/lib/libfreeglut.a" "C:/Program Files (x86)/OpenAL 1.1 SDK/libs/Win32/OpenAL32.lib" "C:/freealut/lib/libalut.dll.a" )

file(COPY res/ DESTINATION res)