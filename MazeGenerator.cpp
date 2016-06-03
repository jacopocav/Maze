//
// Created by Admin on 19/05/2016.
//

#include "MazeGenerator.h"
#include "Settings.h"
#include <algorithm>
#include <chrono>

// Il motore di numeri casuali viene inizializzato usando l'ora di sistema
std::default_random_engine MazeGenerator::rnd(
        static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

std::uniform_real_distribution<float> MazeGenerator::distribution(0.0, 1.0);
bool MazeGenerator::braided = Settings::getInstance()["DEAD_ENDS"] == 0;
const float MazeGenerator::randomness = static_cast<float>(Settings::getInstance()["MAZE_RANDOMNESS"]) / 100;

Maze *MazeGenerator::generateMaze(unsigned height, unsigned width) {
    // activeCells contiene tutte le celle che sono in fase di analisi dall'algoritmo
    // L'algoritmo finirà quando activeCells sarà vuoto
    auto activeCells = std::vector<Coordinates>();

    vector<Direction> directions = {N, S, E, W};

    Maze *maze = new Maze(height, width);

    // L'algoritmo comincia a "scavare" dalla cella di inizio
    activeCells.push_back(Coordinates(1, 1));

    while (!activeCells.empty()) {
        // Mischia le direzioni, in questo modo ne verrà scelta una casuale ogni volta
        std::shuffle(directions.begin(), directions.end(), rnd);
        float random = distribution(rnd); // Valore di scelta casuale
        int index;

        // Per scegliere la cella da esaminare da activeCells, si sceglie:
        // Una cella qualsiasi, con probabilità randomness
        // L'ultima cella inserita in activeCells, con probabilità 1 - randomness
        if (random < randomness && activeCells.size() > 1) {
            index = rnd() % (activeCells.size() - 1);
        } else {
            index = activeCells.size() - 1;
        }


        Coordinates cell = activeCells.at(static_cast<unsigned>(index));
        maze->set(cell, true);
        Coordinates newCell;

        // Viene scelta la prossima scelta in base alla direzione.
        // Le direzioni vengono esaminate in ordine casuale
        for (int i = 0; i < directions.size(); ++i) {
            newCell = cell;
            switch (directions[i]) {
                case N:
                    if (newCell.first < 2) continue;
                    newCell.first -= 2;
                    break;
                case S:
                    if (newCell.first > maze->getHeight() - 3) continue;
                    newCell.first += 2;
                    break;
                case E:
                    if (newCell.second > maze->getWidth() - 3) continue;
                    newCell.second += 2;
                    break;
                case W:
                    if (newCell.second < 2) continue;
                    newCell.second -= 2;
                    break;
            }
            if (newCell != cell && !maze->get(newCell)) { // La nuova cella trovata non è stata visitata precedentemente
                activeCells.push_back(newCell); // Viene aggiunta alle celle attive
                Coordinates middleCell((cell.first + newCell.first) / 2,
                                       (cell.second + newCell.second) / 2);
                // Viene "scavato" il percorso dalla cella corrente a quella nuova
                maze->set(middleCell, true);
                maze->set(newCell, true);

                index = -1;
                break;
            }
        }
        if (index >= 0 && index < activeCells.size()) {
            // Abbiamo finito di esaminare la cella corrente (tutte le celle circostanti ad essa sono già state visitate)
            // La cella corrente viene eliminata da quelle attive
            activeCells.erase(activeCells.begin() + index);
        }
    }

    if (braided) { // Se l'utente ha disattivato i vicoli ciechi, ora vengono rimossi
        for (int x = 1; x < maze->getHeight(); x += 2) {
            for (int y = 1; y < maze->getWidth(); y += 2) {
                cullDeadEnd(maze, std::make_pair(x, y));
            }
        }
    }

    return maze;
}


void MazeGenerator::addAlarmsToMaze(Maze *maze, int alarmCount) {
    for (int i = 0; i < alarmCount; ++i) {
        int x = 0, y = 0;
        bool ok = false;
        while (!ok) {
            // Vengono scelte coordinate casuali
            x = 1 + rnd() % (maze->getHeight() - 2);
            y = 1 + rnd() % (maze->getHeight() - 2);

            /* Le nuove coordinate non devono coincidere con il punto di inizio del giocatore,
             * non devono essere in corrispondenza di un muro,
             * non devono corrispondere ad un altro allarme.
             */
            if ((x != 1 || y != 1) && maze->get(x, y) &&
                !maze->isAlarm(static_cast<unsigned>(x), static_cast<unsigned>(y))) {
                if (maze->getAlarmCount() == 0) ok = true;
                else {
                    for (int k = 0; k < maze->getAlarmCount(); ++k) {
                        /* Viene controllato che le coordinate non siano troppo vicine ad altri allarmi
                         * La distanza minima, in linea d'aria, dev'essere pari al 10% delle dimensioni del labirinto
                         */
                        Coordinates alm = maze->getAlarm(k);
                        if (abs(x - alm.first) > 0.1 * maze->getHeight() &&
                            abs(y - alm.second) > 0.1 * maze->getWidth())
                            ok = true;
                    }
                }
            }
        }

        maze->setAlarm(std::make_pair(x, y));
    }
}


void MazeGenerator::cullDeadEnd(Maze *maze, Coordinates cell) {
    int links = 0; /* Numero di celle percorribili adiacenti a cell
                    * Se la cella ha solo 1 vicino percorribile, allora è un vicolo cieco
                    */

    Coordinates neighbor = cell;
    vector<Coordinates> candidates; // Muri circostanti alla cella candidati all'abbattimento

    if (!maze->get(cell)) return; // La cella è un muro

    if (neighbor.first > 2) { // Cella a nord
        neighbor.first -= 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.first < maze->getHeight() - 2) { // Cella a sud
        neighbor.first += 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.second > 2) { // Cella ad est
        neighbor.second -= 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    neighbor = cell;
    if (neighbor.second < maze->getWidth() - 2) { // Cella ad ovest
        neighbor.second += 1;
        if (maze->get(neighbor)) {
            links++;
        } else {
            candidates.push_back(neighbor);
        }
    }
    if (links == 1) { // Se la cella è un vicolo cieco, viene abbattuto un muro a lei adiacente, in maniera casuale
        std::shuffle(candidates.begin(), candidates.end(), rnd);
        maze->set(candidates[0], true);
    }

}