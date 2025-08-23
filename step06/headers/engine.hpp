#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include "snake.hpp"
#include "fruit.hpp"
#include "wall.hpp"
#include "enemy.hpp"
#include "pathfinding.hpp"
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
    
        // Menu popup
        RectangleShape menuBox;
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
    
        // Direction Arrow elements
        Texture arrowTexture;
        Sprite arrowSprite;
        int currentArrowFrame;            // Current animation frame (0-2)
        Time arrowAnimationTimer;         // Timer for animation
        const float ARROW_ANIMATION_SPEED = 0.2f; // Animation speed in seconds
        const float ARROW_MARGIN = 50.0f; // Distance from camera edge
    
        // Snake start position from level
        Vector2f snakeStartPosition;
    
        // Map dimensions
        Vector2u mapSize; // Dimensioni della mappa in pixel

        Time timeSinceLastMove;

        int currentGameState; 
        int lastGameState;

        // --- Enemy/Pathfinding ---
        std::vector<Enemy> enemies;
        struct MyGrid : GridProvider {
            const Engine* e;
            MyGrid(const Engine* eng) : e(eng) {}
            bool isBlocked(sf::Vector2u t) const override { return e->isBlocked(t); }
            sf::Vector2u size() const override { return e->mapSize; }
        };

public:
    bool isBlocked(sf::Vector2u t) const;
    void updateEnemies(float dt);
    void drawEnemies();
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

    // Direction Arrow functions
    void setupDirectionArrow();
    void updateDirectionArrow();
    void drawDirectionArrow();
    Vector2f calculateArrowPosition(Vector2f snakePos, Vector2f fruitPos);
    float calculateArrowRotation(Vector2f snakePos, Vector2f fruitPos);

    void beginNextLevel();

    // main loop
    void run();
};

#endif //SNAKE_ENGINE_HPP