#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Snake{
public:
    enum Direction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };

private:
    Vector2f position;
    Direction direction;
    bool isHead;
    Sprite sprite;
    static  Texture skinTexture;
    static bool textureLoaded;

public:
    Snake( Vector2f startPosition, Direction dir = RIGHT, bool head = false);

    Vector2f getPosition();
    void setPosition( Vector2f);
    void setDirection(Direction dir);
    Direction getDirection() const;
    void setIsHead(bool head);
    bool getIsHead() const;
    Sprite& getSprite();
    void update();
    static void loadTexture();
};

#endif //SNAKE_SNAKE_HPP