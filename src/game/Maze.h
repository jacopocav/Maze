//
// Created by Admin on 19/05/2016.
//

#pragma once


#include <vector>

namespace game {

// Viene utilizzato questo tipo per indicare le coordinate di una cella nel labirinto
    typedef std::pair<unsigned, unsigned> Coordinates;

    class Maze {
    private:
        std::vector<std::vector<bool>> maze_;
        std::vector<std::vector<bool>> wasHere_;
        std::vector<Coordinates> alarms_;
        const Coordinates start_, end_;

        bool recursiveSolve(int x, int y, int endX, int endY);


    public:
        Maze(unsigned height, unsigned width);

        int getHeight() const;

        int getWidth() const;

        // Ritornano il valore di una cella
        bool get(int row, int col) const;

        bool get(Coordinates coord) const;

        // Impostano il valore di una cella
        void set(int row, int col, bool val);

        void set(Coordinates coord, bool val);

        void setAlarm(Coordinates pos);

        void removeAlarm(Coordinates pos);

        int getAlarmCount() const;

        Coordinates getAlarm(int index);

        bool isAlarm(unsigned row, unsigned col) const;

        bool isAlarm(Coordinates pos) const;

        int pathLength(int startX, int startY, int endX, int endY);
    };
}