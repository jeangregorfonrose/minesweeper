//
// Created by jeang on 12/8/2021.
//

#include "Toolbox.h"
#include "minesweeper.h"
#include <string>

ToolBox *ToolBox::getInstance() {
    if (inst == NULL){
        inst = new ToolBox();
    }
    return inst;
}

ToolBox::ToolBox() {
    // variable for buttons positions
    float x = 0.0;
    float y = 0.0;

    // Create window
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Jean Gregor Fonrose", sf::Style::Titlebar | sf::Style::Close);

    // Create Game State
    gameState = new GameState();
    gameState->setPlayStatus(GameState::PLAYING); // set game state

    // Create new game Button
    x = 32 * 11 + 16; // calculate x position of new game Button
    y = 32 * 16; // calculate y position of new game Button
    newGameButton = new Button(sf::Vector2(x,y), [](){restart();});

    // Create debug Button
    x = 32 * 15 + 16; // calculate x position of debug Button
    y = 32 * 16; // calculate y position of debug Button
    debugButton = new Button(sf::Vector2(x, y), []() { toggleDebugMode(); });

    // Create test#1 Button
    x = 32 * 17 + 16; // calculate x position of test#1 Button
    y = 32 * 16; // calculate y position of test#1 Button
    testButton1 = new Button(sf::Vector2(x, y), []() { launchBoard(1); });

    // Create test#2 Button
    x = 32 * 19 + 16; // calculate x position of test#2 Button
    y = 32 * 16; // calculate y position of test#2 Button
    testButton2 = new Button(sf::Vector2(x, y), []() { launchBoard(2); });
}

ToolBox::~ToolBox() {
    delete inst;
    delete gameState;
    delete newGameButton;
    delete debugButton;
    delete testButton1;
    delete testButton2;
}