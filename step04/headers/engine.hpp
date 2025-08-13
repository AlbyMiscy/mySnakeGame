#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include "snake.hpp"
#include "fruit.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>  
#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace sf;
using namespace std;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

class Engine {
private:
    // Window
    RenderWindow window;
    View camera;  // cam that follow the snake
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    int fruitEatenThisLevel; 
    int fruitEatenTotal;
   
    // Snake
    vector<Snake> snake;
    
    int snakeDirection;
    deque<int> direction; // queue for the direction key pressed
    int speed;
    int sectionToAdd; // how many sections to add to the snake

    // Fruit
    Fruit fruit;

    // Wall
    vector<Wall> wallSection;
    int currentLevel;
    int maxLevels;
    
    vector<string> levels;
    
    Font mainFont;
    Text titleText;
    Text fruitEatenText;
    Text currentLevelText;
    Text gameOver;
    Text pressEnterText;
    
    // Menu texts
    Text menuTitle;
    Text playText;
    Text quitText;
    Text instructionsText;
    
    // Pause popup elements
    RectangleShape pauseOverlay;      // Overlay trasparente
    RectangleShape pauseBox;          // Box del popup
    Text pauseTitle;
    Text pauseInstruction1;
    Text pauseInstruction2;

    // Success level popup elements
    RectangleShape successOverlay;    // Overlay trasparente
    RectangleShape successBox;        // Box del popup
    Text successTitle;
    Text successInstruction1;
    Text successInstruction2;
    
    // Snake start position from level
    Vector2f snakeStartPosition;
    
    // Map dimensions
    Vector2u mapSize; // Dimensioni della mappa in pixel

    Time timeSinceLastMove;

    int currentGameState; 
    int lastGameState;

public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { MENU, RUNNING, PAUSED, GAMEOVER, LEVEL_SUCCESS };

    Engine();

    void startGame();
    
    void input(); 
    void update();
    void draw();
    
    void addDirection(int newDirection);
    
    void newSnake();
    void addSnakeSection();

    void moveFruit();

    void checkLevelFiles();
    void loadLevel(int levelNumber);

    void updateCamera(); 
    void initializeCamera(); 

    void togglePause();

    void setupText(Text *textItem, const Font &font, const string &value, int size, Color color);
    void fixText();
    void updateTextPosition(); 
    void updateTextContent(); 
    
    // Menu functions
    void setupMenu();
    void updateMenuPosition();
    void drawMenu();
    
    // Pause popup functions
    void setupPausePopup();
    void updatePausePopupPosition();
    void drawPausePopup();
    
    // Success level popup functin
    void setupSuccessLevelPopup();
    void updateSuccessLevelPopupPosition();
    void drawSuccessLevelPopup();

    void beginNextLevel();

    // main loop
    void run();
};

#endif //SNAKE_ENGINE_HPP