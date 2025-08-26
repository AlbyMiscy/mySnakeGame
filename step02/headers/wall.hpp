#ifndef SNAKE_WALL_HPP
#define SNAKE_WALL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Wall{
private:
    RectangleShape wallShape;
    static Texture wallTexture; 
    static bool textureLoaded;  

public:
    Wall(Vector2f position, Vector2f size);    

    RectangleShape getShape();
    static void loadWallTexture(); // Method to load the texture once
};

#endif // SNAKE_WALL_HPP