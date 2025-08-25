#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <SFML/Graphics.hpp>

class Snake{
public:
    enum Direction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };

private:
    sf::Vector2f position;
    Direction direction;
    bool isHead;
    sf::Sprite sprite;
    static sf::Texture skinTexture;
    static bool textureLoaded;

public:
    Snake(sf::Vector2f startPosition, Direction dir = RIGHT, bool head = false);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f);
    void setDirection(Direction dir);
    Direction getDirection() const;
    void setIsHead(bool head);
    bool getIsHead() const;
    sf::Sprite& getSprite();
    void update();
    static void loadTexture();
};

#endif //SNAKE_SNAKE_HPP