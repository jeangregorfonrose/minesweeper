//
// Created by jeang on 12/8/2021.
//

#include "GameState.h"
#include "Toolbox.h"
#include <fstream>

// TODO : Done!
// Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;

    // set play status to new game
    playStatus = PLAYING;

    // loop to go through tiles vector
    for (int row = 0; row < dimensions.y; row++) {
        std::vector<Tile*> toAdd;
        sf::Vector2f position;

        for (int column = 0; column < dimensions.x; column++) {
            // calculate the position of the new tile
            position.x = column * 32;
            position.y = row * 32;
            toAdd.push_back(new Tile(position));
        }
        tiles.push_back(toAdd);
    }

    // set random mines
    int minesSet = 0;
    while(minesSet < numberOfMines){
        int x = rand() % dimensions.x;
        int y = rand() % dimensions.y;

        if (!tiles[y][x]->isMine()){
            tiles[y][x]->setMine();
            minesSet++;
        }
    }

    // set the neighbors for the tiles
    for (int row = 0; row < 16; row++) {
        for (int column = 0; column < 25; column++) {
            // get the current tile
            Tile *currentTile = this->getTile(column, row);

            // get the tile's position
            int positionX = currentTile->getLocation().x / 32;
            int positionY = currentTile->getLocation().y / 32;

            // array to hold the pointer to the tile that are neighbors
            std::array<Tile* , 8> neighbors;
            int arrayIndex = 0;

            // find neighbors and add them to the neighbor array
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (this->getTile(positionX + i, positionY + j) != currentTile){
                        neighbors[arrayIndex] = this->getTile(positionX + i, positionY + j);
                        arrayIndex++;
                    }
                }
            }

            // set the neighbors to the current tile
            currentTile->setNeighbors(neighbors);
        }
    }
}

// Constructs a game state based on the size, mine placement, and mine number specified at filepath
GameState::GameState(const char *filepath) {
    dimensions = sf::Vector2i(25, 16);
    numberOfMines = 0;

    // set play status to new game
    playStatus = PLAYING;

    std::ifstream boardFile(filepath);
    int count = 1;
    char currentDigit;
    if (boardFile.is_open()){

        // read files to create tiles for board
        for (int row = 0; row < dimensions.y; row++) {
            std::vector<Tile*> toAdd;
            sf::Vector2f position;

            for (int column = 0; column < dimensions.x; column++) {
                // read digit from file
                boardFile >> currentDigit;

                // calculate the position of the new tile
                position.x = column * 32;
                position.y = row * 32;

                // create new tile
                Tile *newTile = new Tile(position);

                // check if digit is 1 to set tile as a mine
                if (currentDigit == '1'){
                    numberOfMines++;
                    newTile->setMine();
                }

                toAdd.push_back(newTile);
            }
            tiles.push_back(toAdd);
        }

        // set the neighbors for the tiles
        for (int row = 0; row < 16; row++) {
            for (int column = 0; column < 25; column++) {
                // get the current tile
                Tile *currentTile = this->getTile(column, row);

                // get the tile's position
                int positionX = currentTile->getLocation().x / 32;
                int positionY = currentTile->getLocation().y / 32;

                // array to hold the pointer to the tile that are neighbors
                std::array<Tile* , 8> neighbors;
                int arrayIndex = 0;

                // find neighbors and add them to the neighbor array
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (this->getTile(positionX + i, positionY + j) != currentTile){
                            neighbors[arrayIndex] = this->getTile(positionX + i, positionY + j);
                            arrayIndex++;
                        }
                    }
                }

                // set the neighbors to the current tile
                currentTile->setNeighbors(neighbors);
            }
        }

    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }

    // close file
    boardFile.close();
}

// TODO : Done!
// Current count of the number of flags placed on the screen
int GameState::getFlagCount() {
    int flagCount = 0;

    // Draw tiles
    for (int row = 0; row < dimensions.y; row++) {
        for (int column = 0; column < dimensions.x; column++) {
            if (this->getTile(column,row)->getState() == Tile::FLAGGED){
                flagCount++;
            }
        }
    }

    return flagCount;
}

// TODO : Done!
// Current count of the number of mines actually on the board.
int GameState::getMineCount() {
    return numberOfMines;
}

// TODO : Done!
// Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds
Tile* GameState::getTile(int x, int y) {
    // check for out of bound position
    if (y > 15 || y < 0 || x > 24 || x < 0){
        return nullptr;
    }

    //return flag ? tiles[y][x] : nullptr;
    return tiles[y][x];
}

// TODO : Done!
// Returns the play status of the game
GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}

// TODO : Done!
// Sets the play status of the game
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    playStatus = _status;
}
