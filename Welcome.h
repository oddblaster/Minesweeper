//
// Created by chuya on 4/15/2024.
//

#ifndef MINESWEEPER_WELCOME_H
#define MINESWEEPER_WELCOME_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


using namespace std;

struct Welcome {
    sf::RenderWindow window;
    int height;
    int width;

    Welcome(int height, int width){
        this->height = height;
        this->width = width;
        window.create(sf::VideoMode(int(width), int(height)), "MineSweeper", sf::Style::Close);
    }


    //Displays the main menu of the game
    void mainMenu(sf::Font font, string input,int width, int height){
        window.clear(sf::Color::Blue);

        //Creates Intro Message
        sf::Text WelcomeText("WELCOME TO MINESWEEPER!",font,24);
        setText(WelcomeText,width/2,height/2 - 150);
        WelcomeText.setStyle(sf::Text::Underlined);

        //Creates Enter Name Input
        sf::Text enterText("Enter your name:", font,20);
        setText(enterText,width/2, height/2-75);

        sf::Text userInput(input + "|", font, 18);
        setText(userInput,width/2,height/2-45);

        window.draw(userInput);
        window.draw(WelcomeText);
        window.draw(enterText);

    }
    //creates the text and places it
    void setText(sf::Text &text, float x, float y){

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(x, y));
    }

    //Exits the game
    void exit(sf::Event &event){
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }
};


#endif //MINESWEEPER_WELCOME_H
