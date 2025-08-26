#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include "snake.hpp"
#include "fruit.hpp"
#include "wall.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm> 

using namespace sf;
using namespace std;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

class Engine {
private:
    // Window
    RenderWindow window;
    View camera;  // Camera to follow the snake
    const unsigned int FPS = 60;
    static const Time TimePerFrame;
   
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
    
    // Snake start position from level
    Vector2f snakeStartPosition;
    
    // Map dimensions (pixel)
    Vector2u mapSize; 

    Time timeSinceLastMove;

    int currentGameState; 
    int lastGameState;

public:
    enum Direction { UP, RIGHT, DOWN, LEFT };
    enum GameState { RUNNING, PAUSED, GAMEOVER };

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

    void updateCamera(); // Update the camera position
    void initializeCamera(); // Initialize the camera

    void togglePause();


    // main loop
    void run();
};

#endif //SNAKE_ENGINE_HPP