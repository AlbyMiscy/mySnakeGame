#include "engine.hpp"

void Engine::newSnake() {
    snake.clear();
    // Head: right
    snake.emplace_back(snakeStartPosition, Snake::RIGHT, true);
    // Body: right
    snake.emplace_back(Vector2f(snakeStartPosition.x - 20, snakeStartPosition.y), Snake::RIGHT, false);
    snake.emplace_back(Vector2f(snakeStartPosition.x - 40, snakeStartPosition.y), Snake::RIGHT, false);
}

void Engine::addSnakeSection (){
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    Snake::Direction dir = snake[snake.size() - 1].getDirection();
    snake.emplace_back(newSectionPosition, dir, false);
}