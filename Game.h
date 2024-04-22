//
// Created by chuya on 4/15/2024.
//

#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#endif //MINESWEEPER_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Tile.h"
#include <chrono>
#include <thread>
#include <fstream>
using namespace std::chrono;
using namespace std;

struct Game{
    vector<Tile*> tiles;
    sf::RenderWindow window;
    int numMines;
    int colCount;
    int rowCount;
    string gameState;
    bool revealTiles;
    bool pauseClicked;
    bool onleaderboard; 

    const string mine = "files/images/mine.png";
    const string flag = "files/images/flag.png";
    const string tile_hidden = "files/images/tile_hidden.png";
    const string tile_revealed = "files/images/tile_revealed.png";
    const string happy = "files/images/face_happy.png";
    const string lose = "files/images/face_lose.png";
    const string win = "files/images/face_win.png";
    const string digitsImage = "files/images/digits.png";
    const string pause = "files/images/pause.png";
    const string play = "files/images/play.png";
    const string leaderboard = "files/images/leaderboard.png";
    const string leaderboardFile = "files/leaderboard.txt";

    Game(int colCount, int rowCount, int numMines){
        this->colCount = colCount;
        this->rowCount = rowCount;
        this->numMines = numMines;
        window.create(sf::VideoMode(colCount*32,rowCount*32 + 100), "MineSweeper", sf::Style::Close);
    }
    void Timer(chrono::time_point<chrono::high_resolution_clock> &old, sf::Sprite &timer){
        if(!pauseClicked){
            auto dur = chrono::high_resolution_clock::now() - old;
            int count = static_cast<int>(duration_cast<chrono::seconds>(dur).count());
            int min_count = static_cast<int>(duration_cast<chrono::minutes>(dur).count());
            while(count > 60){
                count = count - 60;
            }
            //Creates a vector of characters from the digits
            vector<int> digits;
            while(count > 0){
                int digit = count % 10;
                digits.push_back(abs(digit));
                count = count/10;
            }
            vector<int> min_digits;
            while(min_count > 0){
                int digit = min_count % 10;
                digits.push_back(abs(digit));
                min_count = min_count/10;
            }

            //Displays the digits
            for(int i = 0; i < digits.size();i++){
                sf::Texture texture;
                texture.loadFromFile(digitsImage,sf::IntRect(abs(digits[i])*21,0,21,32));

                timer.setPosition(float(((colCount * 32) - 54) - 21*i),float(32 * (rowCount + 0.5) + 16));
                timer.setTexture(texture);
                window.draw(timer);
            }
            for( int i = 0; i < min_digits.size();i++){
                sf::Texture min_texture;
                min_texture.loadFromFile(digitsImage,sf::IntRect(abs(digits[i])*21,0,21,32));

                timer.setPosition(float(((colCount * 32) - 97) - 21*i),float(32 * (rowCount+ 0.5) + 16));
                timer.setTexture(min_texture);
                window.draw(timer);
            }
        }
    }
    void clearTiles(){
        tiles.clear();
    }

    void createImage(sf::Sprite &Sprite,const string filename,int x, int y) {

        sf::Texture texture;
        texture.loadFromFile(filename);

        Sprite.setPosition(float(x),float(y));
        Sprite.setTexture(texture);
        window.draw(Sprite);

    }

    void placeMines(){
        int minesLayed = 0;

        while(minesLayed < numMines){
            int c = colCount;
            int r = rowCount;

            unsigned int x = rand() % c;
            unsigned int y = rand() % r;

            unsigned long long size = tiles.size();
            for(int i = 0; i < size; i++){
                if(tiles[i]->getCol() == x && tiles[i]->getRow() == y){
                    //cout << "Found Tile at: " << x << "," << y << endl;
                    if(!tiles[i]->getBombStatus()) {
                        tiles[i]->setBombStatus(true);
                        minesLayed++;
                    }
                }
            }
        }

        for(int i = 0; i < tiles.size(); i++){
            Tile* tile = tiles[i];
            vector<Tile*> Neighbors = tile->getNeighbors();
            if(tile->getBombStatus()){
                for(int numTiles = 0; numTiles < Neighbors.size();numTiles++) {
                    if(!Neighbors[numTiles]->getBombStatus()){
                        Neighbors[numTiles]->setBombsNear(Neighbors[numTiles]->getBombsNear() + 1);
                        //cout << tiles[i]->getNeighbors()[tile]->getRow() << "," << tiles[i]->getNeighbors()[tile]->getCol() << endl;
                    }
                }
            }
        }
        cout << "Mines are primed" << endl;
    }
    void setGameState(string newState){
        gameState = newState;
        cout << gameState << endl;
    }
    void HappyFaceButton(sf::Sprite &face) {
        if(gameState == "inGame"){
            createImage(face,happy, ((colCount/2.0)*32) -32,32 * (rowCount + 0.5));
        }
        else if(gameState == "won"){
            createImage(face, win, ((colCount/2.0)*32) - 32, 32 * (rowCount + 0.5));
        }
        else if(gameState == "lost"){
            createImage(face,lose, ((colCount / 2.0) * 32) - 32,32 * (rowCount + 0.5));
        }
    }

    void DebugButton(){
        sf::Sprite debug;
        createImage(debug,"files/images/debug.png",colCount * 32 -304,32 * (rowCount +0.5));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(debug.getGlobalBounds().contains(float(sf::Mouse::getPosition(window).x),float(sf::Mouse::getPosition(window).y)))
            {
                if(revealTiles){
                    revealTiles = false;
                    cout <<  "Concealing Tiles" << endl;
                }
                else{
                    revealTiles = true;
                    cout << "Revealing Tiles" << endl;
                }
            }
        }
    }

    void PauseOrPlay(sf::Sprite &Button){
        if(!pauseClicked) {
            createImage(Button, play, colCount * 32 - 240, 32 * (rowCount + 0.5));

        }
        else{
            createImage(Button, pause, colCount * 32 - 240, 32 * (rowCount + 0.5));

        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(Button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
                if(pauseClicked){
                    pauseClicked = false;
                }
                else{
                    pauseClicked = true;
                }
            }
        }
    }
    /*
    void leaderBoard(){
        createImage(leaderboard,colCount * 32 -176,32 * (rowCount +0.5));
        if(if
    }*/

    void GameSetup(){
        window.clear(sf::Color::White);
        int r = colCount;
        int c = rowCount;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                Tile* newtile = new Tile(i, j);
                tiles.push_back(newtile);
            }
        }

        for(int i = 0; i < tiles.size(); i++){
            /*
            Tile* currentTile = tiles[i];
            int tile_x = currentTile->getCol();
            int tile_y = currentTile->getRow();

            // Loop through adjacent tiles
            for (int tile_col = tile_x - 1; tile_col <= tile_x + 1; tile_col++) {
                for (int tile_row = tile_y - 1; tile_row <= tile_y + 1; tile_row++) {
                    // Skip if current tile or out of bounds
                    if (tile_col == tile_x && tile_row == tile_y) continue;
                    if (tile_col < 0 || tile_col >= colCount || tile_row < 0 || tile_row >= rowCount) continue;

                    // Find the tile in the tiles vector
                    for (int k = 0; k < tiles.size(); k++) {
                        if (tiles[k]->getCol() == tile_col && tiles[k]->getRow() == tile_row) {
                            currentTile->setNeighbor(tiles[k]);
                            // Make sure to set both tiles as neighbors of each other
                        }
                    }
                }
            }*/

            Tile* currentTile = tiles[i];
            int tile_x = currentTile->getCol();
            int tile_y = currentTile->getRow();

            //Loops through adjacent tiles
            for(int tile_col = tile_x-1; tile_col <= tile_x+ 1; tile_col++){
                for(int tile_row = tile_y-1; tile_row <= tile_y + 1; tile_row++){

                    //If it is the current tile skip
                    if (tile_col == tile_x && tile_row == tile_y) continue;
                    //Checks if the difference of values would lead to the mines being out of bounds.
                    if (tile_col < 0 || tile_col >= colCount || tile_row < 0 || tile_row >= rowCount) continue;

                    //Find the tiles based on the columns and rows that are next to the mine
                    for(int tile = 0; tile < tiles.size(); tile++){
                        if(tiles[tile]->getCol() == tile_col && tiles[tile]->getRow() == tile_row){
                            tiles[i]->setNeighbor(tiles[tile]);
                        }
                    }

                }
            }
        }

        cout << "Tiles are set up" << endl;
    }
    void emptyTileReveal(Tile* tile){
        vector<Tile*>temp = tile->getNeighbors();

        //Loops through the tile neighbors
        for(int i = 0; i < temp.size(); i++){

            if(!temp[i]->getBombStatus() && !temp[i]->getClicked()){
                temp[i]->setClicked();
                if(temp[i]->getBombsNear() == 0){
                    emptyTileReveal(temp[i]);
                }
            }
        }
    }

    //the flag marker in which it indicates how many mines are left
    void MinesLeft(sf::Sprite countdown) {
        //Loops through and counts the flags in the tiles
        int countFlags = 0;
        for (int i = 0; i < tiles.size(); i++) {
            if (tiles[i]->getFlagged()) {
                countFlags++;
            }
        }
        int minesLeft = numMines - countFlags;

        //Creates a vector of characters from the digits
        vector<int> digits;
        while(minesLeft > 0){
            int digit = minesLeft % 10;
            digits.push_back(abs(digit));
            minesLeft = minesLeft/10;
        }

        //Displays the digits
        for(int i = 0; i < digits.size();i++){
            sf::Texture texture;
            if(minesLeft < 0){
                texture.loadFromFile(digitsImage,sf::IntRect(210,0,21,32));
                countdown.setPosition(12,float( 32 * (rowCount+ 0.5) + 16));
                countdown.setTexture(texture);
                window.draw(countdown);
            }
            texture.loadFromFile(digitsImage,sf::IntRect(abs(digits[i])*21,0,21,32));

            countdown.setPosition(float(33) + 21*(abs(int(digits.size()-i))),float( 32 * (rowCount+ 0.5) + 16));
            countdown.setTexture(texture);
            window.draw(countdown);
        }

    }
    void displayTiles(){
        for(int i = 0; i < tiles.size(); i++){
            sf::Sprite tile;

            if(!tiles[i]->getClicked()){
                createImage(tile,tile_hidden,tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                if(revealTiles){
                    if(tiles[i]->getBombStatus()){
                        createImage(tile, mine,tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                    }
                }
                if(tiles[i]->getFlagged()){
                    createImage(tile,flag,tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                }
            }
            else{
                createImage(tile, tile_revealed, tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                if(gameState == "lose"){
                    createImage(tile, mine,tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                }
                else if (!tiles[i]->getBombStatus()){

                    if(tiles[i]->getBombsNear() > 0 ){
                        string filepath = "files/images/number_" + to_string(tiles[i]->getBombsNear()) + ".png";
                        createImage(tile, filepath,tiles[i]->getCol()*32,tiles[i]->getRow()*32);
                    }
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(tile.getGlobalBounds().contains(float(sf::Mouse::getPosition(window).x),float(sf::Mouse::getPosition(window).y))){
                    if(!tiles[i]->getFlagged()){
                        cout << "Bombs Near: " << tiles[i]->getBombsNear()<< endl;
                        cout << "BombStatus: " << tiles[i]->getBombStatus() << endl;
                        cout << "Clicked: " <<  tiles[i]->getClicked() << endl;
                        cout << tiles[i]->getRow() << "," << tiles[i]->getCol() << endl;
                        for(int j = 0; j < tiles[i]->getNeighbors().size(); j++){
                            cout << tiles[i]->getNeighbors()[j]->getRow() << "," << tiles[i]->getNeighbors()[j]->getCol() << "|";
                        }
                        if(!tiles[i]->getClicked()){
                            updateBoard(tiles[i]);
                        }
                    }
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                if(tile.getGlobalBounds().contains(float(sf::Mouse::getPosition(window).x),float(sf::Mouse::getPosition(window).y))){
                    if(!tiles[i]->getClicked()){
                        if(!tiles[i]->getFlagged()){
                            tiles[i]->setFlagged();
                        }
                        else if(tiles[i]->getFlagged()){
                            tiles[i]->setFlagged();
                        }
                    }
                }
            }
        }
    }
    void updateBoard(Tile *tile){
        if(!tile->getClicked()) {
            if (tile->getBombStatus()) {
                for(int i = 0; i < tiles.size(); i++) {
                    tiles[i]->setClicked();
                }
                gameState = "lost";
            }
            tile->setClicked();
            if (tile->getBombsNear() == 0) {
                emptyTileReveal(tile);
            }
        }
    }

};

