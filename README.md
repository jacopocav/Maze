# Maze
A simple 3D maze traversal game, made using OpenGL (through freeGLUT) and OpenAL (through freeALUT).<br/>
Project for the Multimedia Systems course<br/>
MSc in Computer Science<br/>
Università degli Studi di Padova<br/>
Made by Jacopo Cavallarin

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

## Implementation details
### Maze generation
The maze is generated randomly using a block-based implementation of the [Growing Tree Algorithm](http://weblog.jamisbuck.org/2011/1/27/maze-generation-growing-tree-algorithm).
The cell selection method can be modified in `config.cfg` (`MAZE_RANDOMNESS`).
It's also possible to generate _braid_ mazes (containing path loops instead of dead ends) through dead end culling after running the main algorithm (this can also be set in `config.cfg`).
Maze size can be changed in settings.
### Alarms
Alarms are placed randomly inside the maze, but some checks prevent them from being placed too close together.
### Time limit
Time limit is not fixed, insted it's based on the average distance between the player and each alarm. The limit is updated each time the player collects an alarm:
- If the newly calculated time limit is higher than the current remaining time, it is used as the new limit.
- Else, remaining time doesn't change.

This was done to make the game less frustrating and to give the player more room for mistakes.
