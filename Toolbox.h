//
// Created by jeang on 11/22/2021.
//

#pragma once
#include "GameState.h"
#include "Button.h"

class ToolBox{
public:
    sf::RenderWindow window;    //SFML application window
    GameState *gameState;       // Primary game state representation
    Button* debugButton;        // Reveals mines in debug mode
    Button* newGameButton;      // Resets / starts new game
    Button* testButton1;        // Loads test board #1
    Button* testButton2;        // Loads test board #2

    // Return a pointer to the singular Toolbox instance. If no instance has been created, should call constructor
    static ToolBox* getInstance();

private:
    inline static ToolBox* inst;

    ToolBox();
    ~ToolBox();
};
