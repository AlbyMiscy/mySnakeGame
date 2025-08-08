#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include "snake.hpp"
#include "fruit.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>

using namespace sf;
using namespace std;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

class Engine {
private:
    // Window
    RenderWindow window;
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

    Time timeSinceLastMove;

public:
    enum Direction { UP, RIGHT, DOWN, LEFT };

    Engine();

    void input(); 
    void addDirection(int newDirection);
    void update();
    
    void draw();

    void newSnake();
    void addSnakeSection();

    void moveFruit();

    // main loop
    void run();
};

#endif //SNAKE_ENGINE_HPP