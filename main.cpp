#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ios>
#include <fstream>
#include "Class.h"
#include "Welcome.h"
#include "Game.h"
#include <chrono>

int colCount;
int rowCount;
int numMines;
using namespace std;
using namespace std::chrono;

void createClock(){

}


int main()
{
    ifstream config("files/config.cfg",ios::in);
    string line;
    getline(config,line);
    colCount = stoi(line);
    cout << "Columns: " << colCount << endl;
    getline(config,line);
    rowCount = stoi(line);
    cout << "Rows: " << rowCount << endl;
    getline(config,line);
    numMines = stoi(line);

    float width = (float(colCount)*32);
    float height = (float(rowCount)*32) + 100;

    Welcome window(height, width);

    //Loads the Font File
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        cerr << "Failed to load Font File" << endl;
        return 1;
    }

    //Load the variables
    string userInput;
    string userName;
    bool SetupBoard = false;
    Player playerOne;

    //Main Game
    while (window.window.isOpen())
    {
        sf::Event event;
        while (window.window.pollEvent(event)) {
            //Creates the main menu

            window.mainMenu(font, userInput,width, height);
            window.window.display();

            //Users are able to input the name of the file
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode != '\b' and userInput.length() <= 10) {
                    if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                        (event.text.unicode >= 'a' && event.text.unicode <= 'z')) {
                        userInput += static_cast<char> (event.text.unicode);
                    }
                } else {
                    if (!userInput.empty()) {
                        userInput.pop_back();
                    }
                }
            }
            //If Enter is Pressed then it would record the name and go to the menu
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

                vector<char> input;
                cout << "Enter is pressed" << endl;
                for (int i = 0; i < userInput.length(); i++) {
                    input.push_back(userInput[i]);
                    if (i == 0) {
                        input[i] = static_cast<char>(toupper(input[i]));
                    } else {
                        input[i] = static_cast<char>(tolower(input[i]));
                    }
                }
                for(int i = 0; i < input.size(); i++) {
                    userName += input[i];
                }
                cout << "Player's Entered Name: " << userName << endl;
                playerOne.setName(userName);
                window.window.close();
            }
        }
    }

    sf::Sprite face;
    sf::Sprite countdown;
    sf::Sprite Timer;
    sf::Sprite PausePlay;
    Game game(colCount, rowCount, numMines);
    game.GameSetup();
    game.placeMines();
    game.setGameState("inGame");
    auto old = chrono::high_resolution_clock::now();
    while(game.window.isOpen()){

        sf::Event event;

        while(game.window.pollEvent(event)){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                cout << face.getPosition().x << "," << face.getPosition().y << endl;
                cout << face.getGlobalBounds().contains(float(sf::Mouse::getPosition().x),float(sf::Mouse::getPosition().y)) << endl;
                cout << sf::Mouse::getPosition(game.window).x << "," << sf::Mouse::getPosition(game.window).y << endl;
                if(face.getGlobalBounds().contains(float(sf::Mouse::getPosition(game.window).x),float(sf::Mouse::getPosition(game.window).y)))
                {
                    game.clearTiles();
                    game.setGameState("inGame");
                    game.GameSetup();
                    game.placeMines();
                }
            }
            if (event.type == sf::Event::Closed) {
                game.window.close();
            }
        }
        game.window.clear(sf::Color::White);
        game.displayTiles();
        game.HappyFaceButton(face);
        game.DebugButton();
        game.MinesLeft(countdown);
        game.Timer(old,Timer);
        game.PauseOrPlay(PausePlay);
        game.window.display();
    }
    return 0;
}