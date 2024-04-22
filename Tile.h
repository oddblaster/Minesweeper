//
// Created by chuya on 4/15/2024.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class Tile{
    int x;
    int y;

    vector<Tile*> neighbors;
    int bombsNear;
    bool bombStatus;
    bool isClicked;
    bool Flagged;
public:
    bool getFlagged();
    void setFlagged();
    Tile(int x, int y);
    int getRow() const;
    int getCol() const;
    int getBombsNear();
    void setBombsNear(int bombs);
    bool getBombStatus();
    void setBombStatus(bool newstatus);
    bool getClicked();
    void setClicked();
    Tile* setNeighbor(Tile *tile);
    vector<Tile*> getNeighbors();
};


#endif //MINESWEEPER_TILE_H
