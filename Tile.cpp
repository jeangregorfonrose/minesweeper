//
// Created by jeang on 12/8/2021.
//

#include "Tile.h"
#include "Toolbox.h"

// TODO : Done!
// Constructs a new tile object at the designated _position
Tile::Tile(sf::Vector2f position) {
    _position = position;
    state = HIDDEN;
    mine = false;
}

// TODO : Done!
// Returns the position of this tile
sf::Vector2f Tile::getLocation() {
    return _position;
}

// TODO : Done!
// Returns current state of this tile
Tile::State Tile::getState() {
    return state;
}

// TODO : Done!
// Sets the state of this tile. Should trigger other behaviors related to the state change(including visualization)
void Tile::setState(Tile::State _state) {
    state = _state;

    // if the tile that got change the state to revealed as a neighbor
    // doesn't have any mines close as neighbor, then clickLeft on this tile
    if (_state == REVEALED){
        // get this current tile
        // count if there is a mine close
        int mineCount = 0;
        for (int i = 0; i < 8; ++i) {
            if (this->getNeighbors()[i] != nullptr && this->getNeighbors()[i]->isMine()) mineCount++;
        }

        // if mine count is 0 it means we can revealed its neighbor also
        if (mineCount == 0) this->revealNeighbors();
    }
}

// Returns pointer to array of Tile pointers
std::array<Tile *, 8> &Tile::getNeighbors() {
    return neighbors;
}

// Populates / Replaces the neighboring tile container
void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
}

// TODO : Done!
// Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries
void Tile::onClickLeft() {
    if (ToolBox::getInstance()->gameState->getPlayStatus() != GameState::LOSS
        && ToolBox::getInstance()->gameState->getPlayStatus() != GameState::WIN)
    {
        if (mine && state != FLAGGED){ // user clicked a mine
            state = EXPLODED;
            ToolBox::getInstance()->gameState->setPlayStatus(GameState::PlayStatus::LOSS); // set the state of the game to loss

            // show mines
            for (int row = 0; row < 16; row++) {
                for (int column = 0; column < 25; column++) {
                    if (ToolBox::getInstance()->gameState->getTile(column,row)->isMine())
                    {
                        ToolBox::getInstance()->gameState->getTile(column,row)->setState(Tile::EXPLODED);
                    }
                }
            }
        }
        else if (state == HIDDEN) {
            state = REVEALED; // set the state to revealed if tile is hidden and doesn't have mine
            this->revealNeighbors(); // reveal the neighbors

            // check if game user has won the game
            // show mines
            bool won = true;

            // check for a single mine that is Hidden and that is not a mine
            // if found that means the user hasn't won the game
            for (int row = 0; row < 16; row++) {
                for (int column = 0; column < 25; column++) {
                    if ((ToolBox::getInstance()->gameState->getTile(column,row)->getState() == HIDDEN
                         && !ToolBox::getInstance()->gameState->getTile(column,row)->isMine() )
                        || ToolBox::getInstance()->gameState->getTile(column,row)->getState() == FLAGGED)
                    {

                        won = false;
                    }
                }
            }

            // if user won change game status
            if (won) ToolBox::getInstance()->gameState->setPlayStatus(GameState::PlayStatus::WIN); // set the state of the game to loss
        }
    }
}

// TODO : Done!
// Toggles this tile's state between FLAGGED and HIDDEN
// Right clicking a tile displays a flag on the tile to mark it as a possible mine
void Tile::onClickRight() {
    if (ToolBox::getInstance()->gameState->getPlayStatus() != GameState::LOSS
        && ToolBox::getInstance()->gameState->getPlayStatus() != GameState::WIN)
    {
        if (state == FLAGGED) state = HIDDEN;
        else if (state == HIDDEN) state = FLAGGED;
    }
}

// TODO : Done!
void Tile::draw() {
    // hold path of the file to load
    std::string path = "../images/";
    // hold name of the file to load
    std::string filename1 = "";
    // hold name of the file to load
    std::string filename2 = "";

    // hold sprite
    sf::Sprite sprite;

    // hold texture
    sf::Texture texture;

    // Hidden tile
    if (state == HIDDEN){
        filename1 = "tile_hidden.png";
    }
    // Revealed tile
    if (state == REVEALED){
        filename1 = "tile_revealed.png";

        // count number of mines close to that tiles to display number on tile
        int minesCount = 0;

        for (int i = 0; i < 8; i++) {
            if (this->getNeighbors()[i] != nullptr){
                if (this->getNeighbors()[i]->isMine()){
                    minesCount++;
                }
            }
        }

        // load the correct image for the number of mines
        if (minesCount != 0) filename2 = "number_" + std::to_string(minesCount) + ".png";
    }

    // Flagged tile
    if (state == FLAGGED){
        filename1 = "tile_hidden.png";
        filename2 = "flag.png";
    }

    // Exploded tile
    if (state == EXPLODED){
        filename1 = "tile_revealed.png";
        filename2 = "mine.png";
    }

    // load first texture and make sprite to draw
    if (!texture.loadFromFile(path + filename1)){
        std::cout << "Could not load the sprite" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setPosition(_position);

    ToolBox::getInstance()->window.draw(sprite); // draw tile to window


    // load second texture and make sprite if needed
    if (state == EXPLODED || state == FLAGGED || (state == REVEALED && filename2 != "")){
        // load second texture
        sf::Texture overlay;
        if (!overlay.loadFromFile(path + filename2)){
            std::cout << "Could not load the sprite" << std::endl;
        }
        sprite.setTexture(overlay);
        sprite.setPosition(_position);

        ToolBox::getInstance()->window.draw(sprite); // draw tile to window
    }
}

// TODO : Done!
// Make this tile have a mine
void Tile::setMine() {
    mine = true;
}

// TODO : Done!
// Know if this tile has mine or not
bool Tile::isMine() {
    return mine;
}

void Tile::revealNeighbors() {
    for (int i = 0; i < 8; i++) {
        if (this->getNeighbors()[i] != nullptr){
            if (this->getNeighbors()[i]->getState() == HIDDEN && !this->getNeighbors()[i]->isMine() && this->getNeighbors()[i]->getState() != FLAGGED){
                this->getNeighbors()[i]->setState(REVEALED);
            }
        }
    }
}