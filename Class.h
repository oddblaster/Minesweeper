//
// Created by chuya on 4/14/2024.
//
#include <iostream>
#include <vector>

#ifndef MINESWEEPER_PLAYER_H
#define MINESWEEPER_PLAYER_H


using namespace std;

class Player {
    int time;
    string name;

public:
    Player();
    Player(string, int time);
    string getName();
    int getTime();
    void setName(string &newName);
    void setTime(int &newTime);
    void Display();
};


#endif //MINESWEEPER_PLAYER_H
