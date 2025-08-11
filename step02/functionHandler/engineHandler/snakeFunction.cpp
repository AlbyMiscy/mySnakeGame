#include "engine.hpp"

// initial snake created at the start
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(snakeStartPosition);
    snake.emplace_back(Vector2f(snakeStartPosition.x - 20, snakeStartPosition.y));
    snake.emplace_back(Vector2f(snakeStartPosition.x - 40, snakeStartPosition.y));
}

void Engine::addSnakeSection (){
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}