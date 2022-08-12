#include "minesweeper.h"
#include <vector>
#include <iostream>

ToolBox *tools;

// path and file name for boards
const char *board1 = "../boards/testboard1.brd";
const char *board2 = "../boards/testboard2.brd";

// hold variable for debug mode to know if active or not
bool debugModeActive = false;

// path and file names for buttons
std::string imagesPath = "../images/";
std::string faceHappy = "face_happy.png";
std::string faceWin = "face_win.png";
std::string faceLose = "face_lose.png";
std::string debugImage = "debug.png";
std::string test1Image = "test_1.png";
std::string test2Image = "test_2.png";
std::string digitImage = "digits.png";

// variables holding texture and sprite for New game button
sf::Sprite restartSprite;
sf::Texture restartTexture;

// variables that hold texture and sprites for digits
sf::Texture digitTexture;
std::vector<sf::Sprite*> mineCounter;

// TODO : Done!
// This method is invoked directly by main() and is responsible for the game’s launch. It should be possible to
// directly invoke this function after including the submitted source and header files in the test suite.
int launch(){
    tools = ToolBox::getInstance();

    // load image to restart button
    if (!restartTexture.loadFromFile(imagesPath + faceHappy)){
        std::cout << "Could not load the sprite" << std::endl;
    }
    restartSprite.setTexture(restartTexture); // set the restart button sprite
    tools->newGameButton->setSprite(&restartSprite);

    // load image to debug button
    sf::Sprite debugSprite;
    sf::Texture debugTexture;
    if (!debugTexture.loadFromFile(imagesPath + debugImage)){
        std::cout << "Could not load the sprite" << std::endl;
    }
    debugSprite.setTexture(debugTexture); // set the restart button sprite
    tools->debugButton->setSprite(&debugSprite);

    // load image to test#1 button
    sf::Sprite test1Sprite;
    sf::Texture test1Texture;
    if (!test1Texture.loadFromFile(imagesPath + test1Image)){
        std::cout << "Could not load the sprite" << std::endl;
    }
    test1Sprite.setTexture(test1Texture); // set the test#1 button sprite
    tools->testButton1->setSprite(&test1Sprite);

    // load image to test#2 button
    sf::Sprite test2Sprite;
    sf::Texture test2Texture;
    if (!test2Texture.loadFromFile(imagesPath + test2Image)){
        std::cout << "Could not load the sprite" << std::endl;
    }
    test2Sprite.setTexture(test2Texture); // set the test#2 button sprite
    tools->testButton2->setSprite(&test2Sprite);

    // load digit image
    if (!digitTexture.loadFromFile(imagesPath + digitImage)){
        std::cout << "Could not load the sprite" << std::endl;
    }
    // create three sprites for digits and add them to the vector mineCounter
    for (int i = 0; i < 3; ++i) {
        mineCounter.push_back(new sf::Sprite(digitTexture));
    }
    // set position for each counter digit display
    for (int i = 0; i < mineCounter.size(); i++) {
        mineCounter.at(i)->setPosition(i * 21, 32 * 16);
    }

    //render board
    render();

    // logic of game
    return gameLoop();
}

// TODO : Done!
// Resets all states/objects and generates a random board and turns off debug mode if active.
void restart(){
    // delete previous GameState
    delete tools->gameState;

    // create new game state
    tools->gameState = new GameState();

    // render for changes
    render();
}

// Start a new game with board data from file
void launchBoard(int boardNumber){
    // delete previous GameState
    delete tools->gameState;

    switch (boardNumber) {
        case 1:
            tools->gameState = new GameState(board1);
            break;
        case 2:
            tools->gameState = new GameState(board2);
            break;
    }

    // render for changes
    render();
}

// change the texture in of the sprites in mineCounter to display the actual number of mine counter
void changeCounter(int counter){
    int digitWidth = 21;
    int digitHeight = 32;

    int digit1 = 0;
    int digit2 = 0;
    int digit3 = 0;

    // get each digit separately
    if ( counter < 100 ){
        digit1 = counter < 0 ? counter / 100 * -1 : counter / 100;
        digit2 = counter < 0 ? counter / 10 * -1 : counter / 10;
        digit3 = counter < 0 ? counter % 10 * -1 : counter % 10;
    }
    else{
        digit1 = counter < 0 ? counter / 100 * -1 : counter / 100;
        digit2 = counter < 0 ? (counter / 10 * -1) % 10 : (counter / 10) % 10;
        digit3 = counter < 0 ? counter % 10 * -1 : counter % 10;
    }

    // change for the first digit
    // check for negative digit to put negative sign
    if (counter < 0){
        // put negative sign
        mineCounter.at(0)->setTextureRect(sf::IntRect(10 * digitWidth, 0, digitWidth, digitHeight));
    }
    else{
        mineCounter.at(0)->setTextureRect(sf::IntRect(digit1 * digitWidth, 0, digitWidth, digitHeight));
    }

    // change for the second digit
    mineCounter.at(1)->setTextureRect(sf::IntRect(digit2 * digitWidth, 0, digitWidth, digitHeight));

    // change for the third digit
    mineCounter.at(2)->setTextureRect(sf::IntRect(digit3 * digitWidth, 0, digitWidth, digitHeight));
}

// Draws the all UI elements according to the current gameState and debug mode.
void render(){
    // Clear the whole window before rendering a new frame
    tools->window.clear();

    // Draw tiles
    for (int row = 0; row < 16; row++) {
        for (int column = 0; column < 25; column++) {
            tools->gameState->getTile(column,row)->draw();
        }
    }

    // calculate the mine counter
    int counter = tools->gameState->getMineCount() - tools->gameState->getFlagCount();

    // update counter
    changeCounter(counter);

    // display counter
    for (int i = 0; i < mineCounter.size(); i++) {
        tools->window.draw(*mineCounter.at(i));
    }
    // check for game status to change face in new game button
    switch (tools->gameState->getPlayStatus()) {
        case GameState::PlayStatus::PLAYING:
        {
            //std::cout << "I am Playing" << std::endl;

            // load face happy for new game button
            if (!restartTexture.loadFromFile(imagesPath + faceHappy)){
                std::cout << "Could not load the sprite" << std::endl;
            }
            break;
        }
        case GameState::PlayStatus::LOSS:
        {
            //std::cout << "I am Losing" << std::endl;

            // load face lose for new game button
            if (!restartTexture.loadFromFile(imagesPath + faceLose)){
                std::cout << "Could not load the sprite" << std::endl;
            }
            break;
        }
        case GameState::PlayStatus::WIN:
        {
            //std::cout << "I am Winning" << std::endl;

            // load face win for new game button
            if (!restartTexture.loadFromFile(imagesPath + faceWin)){
                std::cout << "Could not load the sprite" << std::endl;
            }
            break;
        }
    }

    restartSprite.setTexture(restartTexture); // set the restart button texture
    tools->newGameButton->setSprite(&restartSprite); // set the restart button sprite

    // draw new game button
    tools->window.draw(*tools->newGameButton->getSprite());

    // draw debug button
    tools->window.draw(*tools->debugButton->getSprite());

    // draw test#1 button
    tools->window.draw(*tools->testButton1->getSprite());

    // draw test#2 button
    tools->window.draw(*tools->testButton2->getSprite());

    // End the current frame and display its contents on screen
    tools->window.display();
}

// TODO : Done!
// Flips the debug mode on/off. (Debug mode should initially be off/false.)
void toggleDebugMode(){
    // Don't activate debug mode when user has lost or has won the game
    if (tools->gameState->getPlayStatus() != GameState::LOSS && tools->gameState->getPlayStatus() != GameState::WIN){
        // if debug mode is not active, show the mines and set debug mode active
        if (!getDebugMode()){
            // make debugmode active
            debugModeActive = true;

            // show mines
            for (int row = 0; row < 16; row++) {
                for (int column = 0; column < 25; column++) {
                    if (tools->gameState->getTile(column,row)->isMine()){
                        tools->gameState->getTile(column,row)->setState(Tile::EXPLODED);
                    }
                }
            }
        }
        else{
            // make debug mode inactive
            debugModeActive = false;

            // hide all tiles
            for (int row = 0; row < 16; row++) {
                for (int column = 0; column < 25; column++) {
                    if (tools->gameState->getTile(column,row)->isMine()){
                        tools->gameState->getTile(column,row)->setState(Tile::HIDDEN);
                    }
                }
            }
        }
    }
}

// TODO : Done!
// Returns the true if debug mode is active, and false otherwise.
bool getDebugMode(){
    return debugModeActive;
}

// TODO : Done!
// Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.
int gameLoop(){
    // Start the game loop
    // run the program as long as the window is open
    while (tools->window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (tools->window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                {
                    tools->debugButton->onClick();
                    tools->window.close();
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    switch (event.key.code) {
                        case sf::Mouse::Left:
                        {
                            // get the local mouse position (relative to a window)
                            sf::Vector2i localPosition = sf::Mouse::getPosition(tools->window); // window is a sf::Window

                            // Try getting the tile at that position clicked by checking if a tile is at that position
                            Tile *currentTile = tools->gameState->getTile(localPosition.x / 32, localPosition.y / 32);

                            if (currentTile != nullptr && tools->gameState->getPlayStatus() != GameState::LOSS){
                                currentTile->onClickLeft();
                            }

                            // check for new game button clicked
                            if (tools->newGameButton->getSprite()->getGlobalBounds().contains((float) localPosition.x, (float) localPosition.y)){
                                tools->newGameButton->onClick();
                            }

                            // check for debug button clicked
                            if (tools->debugButton->getSprite()->getGlobalBounds().contains((float) localPosition.x, (float) localPosition.y)){
                                tools->debugButton->onClick();
                            }

                            // check for test#1 button clicked
                            if (tools->testButton1->getSprite()->getGlobalBounds().contains((float) localPosition.x, (float) localPosition.y)){
                                tools->testButton1->onClick();
                            }

                            // check for test#2 button clicked
                            if (tools->testButton2->getSprite()->getGlobalBounds().contains((float) localPosition.x, (float) localPosition.y)){
                                tools->testButton2->onClick();
                            }

                            // render to see changes
                            render();
                            break;
                        }
                        case sf::Mouse::Right:
                        {
                            // get the local mouse position (relative to a window)
                            sf::Vector2i localPosition = sf::Mouse::getPosition(tools->window); // window is a sf::Window

                            // Try getting the tile at that position clicked by checking if a tile is at that position
                            Tile *currentTile = tools->gameState->getTile(localPosition.x / 32, localPosition.y / 32);

                            if (currentTile != nullptr && tools->gameState->getPlayStatus() != GameState::LOSS){
                                currentTile->onClickRight();
                            }

                            // rerender board
                            render();
                            break;
                        }
                    }

                    break;
                }
            }
        }
    }

    // delete pointers used in this part

    return 0;
}

// TODO : Done!
int main() {
    return launch();
}