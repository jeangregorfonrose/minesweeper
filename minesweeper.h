//
// Created by jeang on 11/22/2021.
//
#pragma once
#include "Toolbox.h"

// This method is invoked directly by main() and is responsible for the game’s launch. It should be possible to
// directly invoke this function after including the submitted source and header files in the test suite.
int launch();

// Resets all states/objects and generates a random board and turns off debug mode if active.
void restart();

// Start a new game with board data from file
void launchBoard(int boardNumber);

// change the texture in of the sprites in mineCounter to display the actual number of mine counter
void changeCounter(int counter);

// Draws the all UI elements according to the current gameState and debug mode.
void render();

// Flips the debug mode on/off. (Debug mode should initially be off/false.)
void toggleDebugMode();

// Returns the true if debug mode is active, and false otherwise.
bool getDebugMode();

// Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.
int gameLoop();