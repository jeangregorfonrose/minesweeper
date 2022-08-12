//
// Created by jeang on 11/22/2021.
//

#pragma once
#include "Tile.h"
#include <vector>
#include <SFML\Graphics.hpp>

class GameState{
public:
    // Tracks the play status of the game, which is reflected in the behavior of the user interface and visualizations
    enum PlayStatus {WIN,LOSS,PLAYING};

    // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines
    explicit GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);

    // Constructs a game state based on the size, mine placement, and mine number specified at filepath
    GameState(const char* filepath);

    // Current count of the number of flags placed on the screen
    int getFlagCount();

    // Current count of the number of mines actually on the board.
    int getMineCount();

    // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds
    Tile* getTile(int x, int y);

    // Returns the play status of the game
    PlayStatus getPlayStatus();

    // Sets the play status of the game
    void setPlayStatus(PlayStatus _status);

private:
    sf::Vector2i dimensions;
    int numberOfMines;
    std::vector<std::vector<Tile*>> tiles;
    PlayStatus playStatus;
};
