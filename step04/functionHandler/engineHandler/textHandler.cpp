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

    setupText(&currentLevelText, mainFont, "level 1", 15, Color::Blue);
    setupText(&fruitEatenText, mainFont, "fruit 0", 15, Color::Blue);
}

void Engine::updateTextPosition(){
    Vector2f cameraCenter = camera.getCenter();
    
    // Title
    FloatRect titleTextBounds = titleText.getLocalBounds();
    float titleX = cameraCenter.x - (titleTextBounds.size.x / 2.0f);
    float titleY = cameraCenter.y - (WINDOW_HEIGHT / 2.0f) + 20.0f; 
    titleText.setPosition(Vector2f(titleX, titleY));
    
    // Current Level
    float leftMargin = 20.0f;
    float currentLevelX = cameraCenter.x - (WINDOW_WIDTH / 2.0f) + leftMargin;
    float currentLevelY = cameraCenter.y - (WINDOW_HEIGHT / 2.0f) + 20.0f;
    currentLevelText.setPosition(Vector2f(currentLevelX, currentLevelY));
    
    // Fruit Eaten
    float fruitEatenX = cameraCenter.x - (WINDOW_WIDTH / 2.0f) + leftMargin;
    float fruitEatenY = cameraCenter.y - (WINDOW_HEIGHT / 2.0f) + 50.0f; 
    fruitEatenText.setPosition(Vector2f(fruitEatenX, fruitEatenY));
}

void Engine::updateTextContent(){
    // Update current level's text
    currentLevelText.setString("Level: " + to_string(currentLevel));
    
    // Update eaten fruit's text
    fruitEatenText.setString("Fruits: " + to_string(fruitEatenThisLevel));
}