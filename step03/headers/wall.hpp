#ifndef SNAKE_WALL_HPP
#define SNAKE_WALL_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall{
private:
    RectangleShape wallShape;
    static Texture wallTexture; 
    static bool textureLoaded;  

public:
    Wall(Vector2f position, Vector2f size);    

    RectangleShape getShape();
    static void loadWallTexture(); 
};

#endif // SNAKE_WALL_HPP