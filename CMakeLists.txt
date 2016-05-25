cmake_minimum_required(VERSION 3.5)
project(Maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Camera.h Camera.cpp MazeGenerator.cpp MazeGenerator.h Maze.cpp Maze.h GlutUtils.cpp GlutUtils.h MazeCamera.cpp MazeCamera.h)
add_executable(Maze ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} "C:/freeglut/include")
target_link_libraries(Maze ${OPENGL_LIBRARIES} "C:/freeglut/lib/libfreeglut.a" )