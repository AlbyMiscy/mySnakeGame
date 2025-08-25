

#include "snake.hpp"
#include <iostream>

sf::Texture Snake::skinTexture;
bool Snake::textureLoaded = false;

void Snake::loadTexture() {
    if (!textureLoaded) {
        if (!skinTexture.loadFromFile("resources/texture/skin/snake_skin_1.png")) {
            std::cerr << "Error: Could not load snake skin texture!" << std::endl;
            return;
        }
        textureLoaded = true;
    }
}

Snake::Snake(sf::Vector2f startPosition, Direction dir, bool head)
    : position(startPosition), direction(dir), isHead(head), sprite(skinTexture) {
    loadTexture();
    setDirection(dir);
    setIsHead(head);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(1.f, 1.f)); // 20x20, no scaling needed
}

sf::Vector2f Snake::getPosition() {
    return position;
}

void Snake::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
    sprite.setPosition(position);
}

void Snake::setDirection(Direction dir) {
    direction = dir;
    // Select correct sprite from texture
    int row = isHead ? 0 : 1;
    int col = static_cast<int>(dir);
    sf::IntRect rect(sf::Vector2i(col * 20, row * 20), sf::Vector2i(20, 20));
    sprite.setTextureRect(rect);
}

Snake::Direction Snake::getDirection() const {
    return direction;
}

void Snake::setIsHead(bool head) {
    isHead = head;
    setDirection(direction); // Update texture rect
}

bool Snake::getIsHead() const {
    return isHead;
}

sf::Sprite& Snake::getSprite() {
    return sprite;
}

void Snake::update() {
    sprite.setPosition(position);
    setDirection(direction); // Ensure correct sprite
}