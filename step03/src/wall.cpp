#include "wall.hpp"

Texture Wall::wallTexture;
bool Wall::textureLoaded = false;

void Wall::loadWallTexture() {
    if (!textureLoaded) {
        if (!wallTexture.loadFromFile("resources/texture/wall.png")) {
        }
        textureLoaded = true;
    }
}

Wall::Wall(Vector2f position, Vector2f size){
    wallShape.setSize(size);
    wallShape.setPosition(position);
    
    loadWallTexture();
    
    if (textureLoaded && wallTexture.getSize().x > 0) {
        wallShape.setTexture(&wallTexture);
    } else {
        wallShape.setFillColor(Color::White);
    }
}

RectangleShape Wall::getShape(){
    return wallShape;
}