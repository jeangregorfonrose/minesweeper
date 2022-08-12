//
// Created by jeang on 11/22/2021.
//

#pragma once
#include <SFML/Graphics.hpp>

class Button{
private:
    sf::Sprite *sprite;
    sf::Vector2f position;
    std::function<void(void)> clickFunction;

public:
    // Construct a new object at the specified _position which invokes the _onClick callback when clicked
    Button(sf::Vector2f _position, std::function<void(void)> _onClick){
        position = _position;
        clickFunction = _onClick;

    }

    // Returns the position of the button
    sf::Vector2f getPosition(){
        return position;
    }

    // Returns the current sprite of the button
    sf::Sprite* getSprite(){
        return sprite;
    }

    // Sets this button's visualization to the specified _sprite
    void setSprite(sf::Sprite* _sprite){
        sprite = _sprite;
        sprite->setPosition(position);
    }

    // Invokes the button's callback method (usually called when clicked)
    void onClick(){
        this->clickFunction();
    }
};
