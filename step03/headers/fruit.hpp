#ifndef SNAKE_FRUIT_HPP
#define SNAKE_FRUIT_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <memory>

using namespace sf;
using namespace std;

class Fruit {
private:
    unique_ptr<Sprite> sprite;
    static Texture texture;
    static bool textureLoaded;
    int currentSpriteIndex;
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dis;

public:
    Fruit();

    void setPosition(Vector2f position);
    void randomizeSprite();
    Sprite& getSprite();
    
private:
    void loadTexture();

};

#endif //SNAKE_FRUIT_HPP