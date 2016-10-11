# Maze
A simple 3D maze traversal game, made using OpenGL (through freeGLUT) and OpenAL (through freeALUT).<br/>
Project for the Multimedia Systems course<br/>
MSc in Computer Science<br/>
Università degli Studi di Padova<br/>

## Requirements
OpenGL and OpenAL must be installed for the game to work. In the `executable` directory, a pre-compiled version of the game can be found.
`freeglut.dll` and `libalut.dll` are also necessary, and are already included.
The game has been tested only on Windows, but no OS specific code has been used, so it should work on other OS with little to no adjustments.

## Objective
The game's objective is to traverse the maze and deactivate the alarms randomly placed in it within a time limit.
The alarms emit a sound that helps the player locate them.
To deactivate an alarm, the player just has to go through them.
After deactivating an alarm, the time limit can increase if the remaining alarms are far away.
The player wins if they manage to collect all the alarms before time runs out.

## Controls
                      SPACE - Start the game and pause/unpause
                          R - Restart the game (a new maze will be created)
                        W,S - Move forward/backward
                        A,D - Strafe left/right
                      Mouse - Move view
         LEFT, RIGHT arrows - Rotate view horizontally
      Right click, UP arrow - Fly up (if flight enabled)
     Left click, DOWN arrow - Fly down (if flight enabled)


## Settings
The file `res/config.cfg` contains some settings that can be modified by the user.
For a description of every setting, please consult the file itself.
