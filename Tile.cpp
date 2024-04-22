//
// Created by chuya on 4/15/2024.
//

#include "Tile.h"
#include <random>


using namespace std;

Tile::Tile(int x, int y) {
    this->x = x;
    this->y = y;
    bombStatus = false;
    bombsNear = 0;
    Flagged = false;
}

int Tile::getCol() const{
    return x;
}

int Tile::getRow() const{
    return y;
}

bool Tile::getBombStatus() {
    return bombStatus;
}

void Tile::setBombStatus(bool newstatus) {
    bombStatus = newstatus;
}
int Tile::getBombsNear() {
    return bombsNear;
}
void Tile::setBombsNear(int bombs){
    bombsNear = bombs;
}
void Tile::setClicked() {
    isClicked = true;
}
bool Tile::getClicked() {
    return isClicked;
}
Tile* Tile::setNeighbor(Tile *tile){
    neighbors.push_back(tile);
}

vector<Tile*> Tile::getNeighbors(){
    return neighbors;
}
bool Tile::getFlagged() {
    return Flagged;
}
void Tile::setFlagged(){
    if(Flagged){
        Flagged = false;
    }
    else{
        Flagged = true;
    }
}
