#include "wall.hpp"
#include <iostream>

using namespace std;

// Definizione delle variabili statiche
Texture Wall::wallTexture;
bool Wall::textureLoaded = false;

void Wall::loadWallTexture() {
    if (!textureLoaded) {
        if (!wallTexture.loadFromFile("resources/texture/wall.png")) {
            // Texture non disponibile, useremo il colore di default
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