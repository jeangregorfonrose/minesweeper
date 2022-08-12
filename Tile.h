//
// Created by jeang on 11/22/2021.
//

#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Tile{
public:
    // Represents tile's current UI state (visualization)
    enum State {REVEALED,HIDDEN,FLAGGED,EXPLODED};

    // Constructs a new tile object at the designated _position
    explicit Tile(sf::Vector2f position);

    // Returns the position of this tile
    sf::Vector2f getLocation();

    // Returns current state of this tile
    State getState();

    // Sets the state of this tile. Should trigger other behaviors related to the state change(including visualization)
    void setState(State _state);

    // Returns pointer to array of Tile pointers
    std::array<Tile*, 8>& getNeighbors();

    // Populates / Replaces the neighboring tile container
    void setNeighbors(std::array<Tile*, 8> _neighbors);

    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries
    void onClickLeft();

    // Toggles this tile's state between FLAGGED and HIDDEN
    void onClickRight();

    // Render this tile to the screen according to is state
    void draw();

    // Make this tile have a mine
    void setMine();

    // Know if this tile has mine or not
    bool isMine();
protected:
    // Based on State and mine content of the tile neighbors, set their state to REVEALED
    void revealNeighbors();

private:
    State state;
    sf::Vector2f _position;
    bool mine;
    std::array<Tile *, 8> neighbors;
};
