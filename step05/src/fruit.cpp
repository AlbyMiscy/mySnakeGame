#include "fruit.hpp"

Texture Fruit::texture;
bool Fruit::textureLoaded = false;

Fruit::Fruit() : gen(rd()), dis(0, 2) {
    loadTexture();
    
    // Create sprite with the loaded texture
    sprite =  make_unique<Sprite>(texture);
    
    Vector2f startPosition(400, 300);
    sprite->setPosition(startPosition);
    sprite->setScale(Vector2f(1.25f, 1.25f)); // Scale to 20x20 from 16x16
    
    randomizeSprite();
}

void Fruit::loadTexture() {
    if (!textureLoaded) {
        if (!texture.loadFromFile("resources/texture/fruit.png")) {
             cerr << "Error: Could not load fruit texture!" <<  endl;
            return;
        }
        textureLoaded = true;
    }
}

void Fruit::setPosition(Vector2f newPosition) {
    sprite->setPosition(newPosition);
}

void Fruit::randomizeSprite() {
    currentSpriteIndex = dis(gen);
    
    // Each sprite is 16x16, and they are arranged horizontally
    IntRect textureRect(Vector2i(currentSpriteIndex * 16, 0), Vector2i(16, 16));
    sprite->setTextureRect(textureRect);
}

Sprite& Fruit::getSprite() {
    return *sprite;
}