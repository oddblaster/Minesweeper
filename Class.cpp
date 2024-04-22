//
// Created by chuya on 4/14/2024.
//

#include "Class.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

string Player::getName() {
    return name;
}

int Player::getTime() {
    return time;
}

void Player::Display() {
    cout << "Class Name: " << name << endl;
    cout << "Time: " << time << endl;
}

void Player::setName(std::string &newName) {
    name = newName;
}
void Player::setTime(int &newTime) {
    time = newTime;
}

Player::Player(string name, int time) {
    this->name = name;
    this->time = time;
}

Player::Player() {
    this->name = "";
    this->time = 0;
}


