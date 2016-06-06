//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <vector>

namespace game {

// Viene utilizzato questo tipo per indicare le coordinate di una cella nel labirinto
    typedef std::pair<unsigned, unsigned> Coordinates;

    class Maze {
        friend class MazeGenerator;
    private:
        std::vector<std::vector<bool>> maze_;
        std::vector<std::vector<bool>> wasHere_;
        std::vector<Coordinates> alarms_;
        bool isBraided_;
        bool recursiveSolve(int x, int y, int endX, int endY);


    public:
        Maze(unsigned height, unsigned width);

        int getHeight() const;

        int getWidth() const;

        // Ritornano il valore di una cella
        bool get(int row, int col) const;

        bool get(Coordinates coord) const;

        void removeAlarm(Coordinates pos);

        int getAlarmCount() const;

        Coordinates getAlarm(int index) const;

        bool isAlarm(unsigned row, unsigned col) const;

        bool isAlarm(Coordinates pos) const;

        bool isBraided() const;

        int pathLength(Coordinates start, Coordinates end);
    };
}