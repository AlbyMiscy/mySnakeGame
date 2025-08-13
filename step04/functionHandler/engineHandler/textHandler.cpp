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
    setupText(&gameOver, mainFont, "GAME OVER", 72, Color::Yellow);
    setupText(&pressEnterText, mainFont, "Press ENTER to restart", 20, Color::White);
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

    // Game Over
    FloatRect gameOverBounds = gameOver.getLocalBounds();
    float gameOverX = cameraCenter.x - (gameOverBounds.size.x / 2.0f);
    float gameOverY = cameraCenter.y - (gameOverBounds.size.y / 2.0f);
    gameOver.setPosition(Vector2f(gameOverX, gameOverY));
    
    // Press Enter Text
    FloatRect pressEnterBounds = pressEnterText.getLocalBounds();
    float pressEnterX = cameraCenter.x - (pressEnterBounds.size.x / 2.0f);
    float pressEnterY = gameOverY + gameOverBounds.size.y + 20.0f; // 20px di distanza
    pressEnterText.setPosition(Vector2f(pressEnterX, pressEnterY));
}

void Engine::updateTextContent(){
    // Update current level's text
    currentLevelText.setString("Level: " + to_string(currentLevel));
    
    // Update eaten fruit's text
    fruitEatenText.setString("Fruits: " + to_string(fruitEatenThisLevel));
}

void Engine::setupMenu(){
    setupText(&menuTitle, mainFont, "SNAKE GAME", 48, Color::Green);
    setupText(&playText, mainFont, "Press ENTER to Play", 24, Color::White);
    setupText(&quitText, mainFont, "Press ESC to Quit", 20, Color(128, 128, 128)); // Gray color
    setupText(&instructionsText, mainFont, "Use Arrow Keys to Move or 'P' to Pause the game", 16, Color::Yellow);
}

void Engine::updateMenuPosition(){
    // Center all menu items on screen
    Vector2f center(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    
    // Menu Title
    FloatRect menuTitleBounds = menuTitle.getLocalBounds();
    float menuTitleX = center.x - (menuTitleBounds.size.x / 2.0f);
    float menuTitleY = center.y - 100.0f;
    menuTitle.setPosition(Vector2f(menuTitleX, menuTitleY));
    
    // Play Text
    FloatRect playTextBounds = playText.getLocalBounds();
    float playTextX = center.x - (playTextBounds.size.x / 2.0f);
    float playTextY = center.y - 20.0f;
    playText.setPosition(Vector2f(playTextX, playTextY));
    
    // Instructions
    FloatRect instructionsBounds = instructionsText.getLocalBounds();
    float instructionsX = center.x - (instructionsBounds.size.x / 2.0f);
    float instructionsY = center.y + 20.0f;
    instructionsText.setPosition(Vector2f(instructionsX, instructionsY));
    
    // Quit Text
    FloatRect quitTextBounds = quitText.getLocalBounds();
    float quitTextX = center.x - (quitTextBounds.size.x / 2.0f);
    float quitTextY = center.y + 60.0f;
    quitText.setPosition(Vector2f(quitTextX, quitTextY));
}

void Engine::drawMenu(){
    window.clear(Color::Black);
    
    updateMenuPosition();
    
    window.draw(menuTitle);
    window.draw(playText);
    window.draw(instructionsText);
    window.draw(quitText);
    
    window.display();
}

void Engine::setupPausePopup(){
    // Setup overlay (semi-transparent background)
    pauseOverlay.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    pauseOverlay.setFillColor(Color(0, 0, 0, 128)); // Black with 50% transparency
    
    // Setup popup box
    pauseBox.setSize(Vector2f(500, 300));
    pauseBox.setFillColor(Color(50, 50, 50, 220)); // Dark gray, almost opaque
    pauseBox.setOutlineThickness(3);
    pauseBox.setOutlineColor(Color::White);
    
    // Setup texts
    setupText(&pauseTitle, mainFont, "PAUSED", 48, Color::Yellow);
    setupText(&pauseInstruction1, mainFont, "Press P to Resume", 24, Color::White);
    setupText(&pauseInstruction2, mainFont, "Press ESC to Quit", 20, Color(200, 200, 200));
}

void Engine::updatePausePopupPosition(){
    Vector2f cameraCenter = camera.getCenter();
    
    // Position overlay to cover the camera view
    pauseOverlay.setPosition(Vector2f(
        cameraCenter.x - (WINDOW_WIDTH / 2.0f),
        cameraCenter.y - (WINDOW_HEIGHT / 2.0f)
    ));
    
    // Center the popup box
    Vector2f boxSize = pauseBox.getSize();
    pauseBox.setPosition(Vector2f(
        cameraCenter.x - (boxSize.x / 2.0f),
        cameraCenter.y - (boxSize.y / 2.0f)
    ));
    
    // Position texts inside the box
    FloatRect pauseTitleBounds = pauseTitle.getLocalBounds();
    pauseTitle.setPosition(Vector2f(
        cameraCenter.x - (pauseTitleBounds.size.x / 2.0f),
        cameraCenter.y - 80.0f
    ));
    
    FloatRect instruction1Bounds = pauseInstruction1.getLocalBounds();
    pauseInstruction1.setPosition(Vector2f(
        cameraCenter.x - (instruction1Bounds.size.x / 2.0f),
        cameraCenter.y + 10.0f
    ));
    
    FloatRect instruction2Bounds = pauseInstruction2.getLocalBounds();
    pauseInstruction2.setPosition(Vector2f(
        cameraCenter.x - (instruction2Bounds.size.x / 2.0f),
        cameraCenter.y + 50.0f
    ));
}

void Engine::drawPausePopup(){
    updatePausePopupPosition();
    
    // Draw overlay first (makes background transparent)
    window.draw(pauseOverlay);
    
    // Draw popup box
    window.draw(pauseBox);
    
    // Draw texts
    window.draw(pauseTitle);
    window.draw(pauseInstruction1);
    window.draw(pauseInstruction2);
    
    window.display();
}