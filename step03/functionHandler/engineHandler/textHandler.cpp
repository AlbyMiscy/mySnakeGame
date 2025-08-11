#include "engine.hpp"

void Engine::setupText(Text *textItem, const Font &font, const string &value, int size, Color color){
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(color);
}

void Engine::fixText(){
    setupText(&titleText, mainFont, "SnakeGame!", 28, Color::Blue);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    float textX = (WINDOW_WIDTH - titleTextBounds.size.x) / 2.0f;  
    float textY = 20.0f;  
    titleText.setPosition(Vector2f(textX, textY));  
}

void Engine::updateTextPosition(){
    Vector2f cameraCenter = camera.getCenter();
    
    FloatRect titleTextBounds = titleText.getLocalBounds();
    float textX = cameraCenter.x - (titleTextBounds.size.x / 2.0f);
    float textY = cameraCenter.y - (WINDOW_HEIGHT / 2.0f) + 20.0f; 
    
    titleText.setPosition(Vector2f(textX, textY));
}