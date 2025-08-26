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
    Vector2f camSize = camera.getSize();
    // Title
    FloatRect titleTextBounds = titleText.getLocalBounds();
    float titleX = cameraCenter.x - (titleTextBounds.size.x / 2.0f);
    float titleY = cameraCenter.y - (camSize.y / 2.0f) + 20.0f;
    titleText.setPosition(Vector2f(titleX, titleY));
    // Current Level
    float leftMargin = 20.0f;
    float currentLevelX = cameraCenter.x - (camSize.x / 2.0f) + leftMargin;
    float currentLevelY = cameraCenter.y - (camSize.y / 2.0f) + 20.0f;
    currentLevelText.setPosition(Vector2f(currentLevelX, currentLevelY));
    // Fruit Eaten
    float fruitEatenX = cameraCenter.x - (camSize.x / 2.0f) + leftMargin;
    float fruitEatenY = cameraCenter.y - (camSize.y / 2.0f) + 50.0f;
    fruitEatenText.setPosition(Vector2f(fruitEatenX, fruitEatenY));
    // Game Over
    FloatRect gameOverBounds = gameOver.getLocalBounds();
    float gameOverX = cameraCenter.x - (gameOverBounds.size.x / 2.0f);
    float gameOverY = cameraCenter.y - (gameOverBounds.size.y / 2.0f);
    gameOver.setPosition(Vector2f(gameOverX, gameOverY));
    // Press Enter Text
    FloatRect pressEnterBounds = pressEnterText.getLocalBounds();
    float pressEnterX = cameraCenter.x - (pressEnterBounds.size.x / 2.0f);
    float pressEnterY = gameOverY + gameOverBounds.size.y + 20.0f;
    pressEnterText.setPosition(Vector2f(pressEnterX, pressEnterY));
}

void Engine::updateTextContent(){
    // Update current level's text
    currentLevelText.setString("Level: " + to_string(currentLevel));
    
    // Update eaten fruit's text
    fruitEatenText.setString("Fruits: " + to_string(fruitEatenThisLevel));
}

// Centra l'origine del testo (tiene conto del top negativo dei font)
static inline void centerOrigin(Text& t) {
    FloatRect b = t.getLocalBounds();
    t.setOrigin(Vector2f(b.position.x + b.size.x * 0.5f, b.position.y + b.size.y * 0.5f));
}

static inline int scaledPx(float viewH, float pct, int minPx, int maxPx) {
    int px = static_cast<int>(round(viewH * pct));
    return max(minPx, min(px, maxPx));
}

void Engine::setupMenu() {
    setupText(&menuTitle,        mainFont, "SNAKE GAME", 42, Color::Green);
    setupText(&playText,         mainFont, "Press ENTER to Play", 20, Color::White);
    setupText(&instructionsText, mainFont, "Use Arrow Keys to Move or 'P' to Pause the game", 14, Color::Yellow);
    setupText(&quitText,         mainFont, "Press ESC to Quit", 16, Color(128,128,128));

    menuBox.setFillColor(Color(30,30,30,220));
    menuBox.setOutlineThickness(2);
    menuBox.setOutlineColor(Color::White);
}

void Engine::updateMenuPosition() {
    const Vector2f camSize   = camera.getSize();
    const Vector2f camCenter = camera.getCenter();
    const float H = camSize.y;

    int szTitle =  scaledPx(H, 0.10f, 22, 120);
    int szPlay  =  scaledPx(H, 0.050f, 14, 60);
    int szInstr =  scaledPx(H, 0.033f, 12, 50);
    int szQuit  =  scaledPx(H, 0.030f, 12, 46);

    menuTitle.setCharacterSize(szTitle);
    playText.setCharacterSize(szPlay);
    instructionsText.setCharacterSize(szInstr);
    quitText.setCharacterSize(szQuit);

    centerOrigin(menuTitle);
    centerOrigin(playText);
    centerOrigin(instructionsText);
    centerOrigin(quitText);

    float padY = clamp(H * 0.014f, 8.f, 22.f);
    float padX = clamp(camSize.x * 0.030f, 18.f, 48.f);
    float gap  = clamp(H * 0.010f, 6.f, 18.f);

    auto lh = [](const Text& t){ return t.getLocalBounds().size.y; };
    auto lw = [](const Text& t){ return t.getLocalBounds().size.x; };

    auto recompute = [&](float& hTitle, float& hPlay, float& hInstr, float& hQuit,
                         float& textTotalH, float& maxW)
    {
        hTitle = lh(menuTitle);
        hPlay  = lh(playText);
        hInstr = lh(instructionsText);
        hQuit  = lh(quitText);
        textTotalH = hTitle + hPlay + hInstr + hQuit + 3.f * gap;
        maxW = max(max(lw(menuTitle), lw(playText)),
                        max(lw(instructionsText), lw(quitText)));
    };

    float hTitle, hPlay, hInstr, hQuit, textTotalH, maxW;
    recompute(hTitle, hPlay, hInstr, hQuit, textTotalH, maxW);

    const float maxBoxW = camSize.x * 0.85f;
    const float maxBoxH = camSize.y * 0.45f;

    float estBoxW = maxW + 2.f * padX;
    float estBoxH = textTotalH + 2.f * padY;

    float shrinkW = (estBoxW > maxBoxW) ? (maxBoxW / estBoxW) : 1.f;
    float shrinkH = (estBoxH > maxBoxH) ? (maxBoxH / estBoxH) : 1.f;
    float shrink  = min(shrinkW, shrinkH);

    if (shrink < 1.f) {
        szTitle = max(12, static_cast<int>(floor(szTitle * shrink)));
        szPlay  = max(10, static_cast<int>(floor(szPlay  * shrink)));
        szInstr = max(10, static_cast<int>(floor(szInstr * shrink)));
        szQuit  = max(10, static_cast<int>(floor(szQuit  * shrink)));

        menuTitle.setCharacterSize(szTitle);
        playText.setCharacterSize(szPlay);
        instructionsText.setCharacterSize(szInstr);
        quitText.setCharacterSize(szQuit);

        centerOrigin(menuTitle);
        centerOrigin(playText);
        centerOrigin(instructionsText);
        centerOrigin(quitText);

        gap  *= clamp(shrink, 0.75f, 1.f);
        padX *= clamp(shrink, 0.75f, 1.f);
        padY *= clamp(shrink, 0.75f, 1.f);

        recompute(hTitle, hPlay, hInstr, hQuit, textTotalH, maxW);
    }

    Vector2f boxSize(maxW + 2.f*padX, textTotalH + 2.f*padY);
    menuBox.setSize(boxSize);
    menuBox.setPosition(camCenter - boxSize * 0.5f);

    float y = camCenter.y - textTotalH * 0.5f;

    menuTitle.setPosition({camCenter.x, y + hTitle * 0.5f});
    y += hTitle + gap;

    playText.setPosition({camCenter.x, y + hPlay * 0.5f});
    y += hPlay + gap;

    instructionsText.setPosition({camCenter.x, y + hInstr * 0.5f});
    y += hInstr + gap;

    quitText.setPosition({camCenter.x, y + hQuit * 0.5f});
}

void Engine::drawMenu() {
    window.setView(camera);
    updateMenuPosition();
    window.clear(Color::Black);
    window.draw(menuBox);
    window.draw(menuTitle);
    window.draw(playText);
    window.draw(instructionsText);
    window.draw(quitText);
    window.display();
}


void Engine::setupPausePopup(){
    // Setup overlay (semi-transparent background)
    pauseOverlay.setSize(Vector2f(camera.getSize()));
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
    Vector2f camSize = camera.getSize();
    pauseOverlay.setSize(camSize);
    pauseOverlay.setPosition(Vector2f(
        cameraCenter.x - (camSize.x / 2.0f),
        cameraCenter.y - (camSize.y / 2.0f)
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
    // Update positions only once per frame
    updatePausePopupPosition();
    
    // Draw overlay first (makes background transparent)
    window.draw(pauseOverlay);
    
    // Draw popup box
    window.draw(pauseBox);
    
    // Draw texts
    window.draw(pauseTitle);
    window.draw(pauseInstruction1);
    window.draw(pauseInstruction2);
    
    // Display everything at once to prevent flickering
    window.display();
}

void Engine::setupSuccessLevelPopup(){
    // Setup overlay (semi-transparent background)
    successOverlay.setSize(Vector2f(camera.getSize()));
    successOverlay.setFillColor(Color(0, 0, 0, 128)); // Black with 50% transparency
    
    // Setup popup box
    successBox.setSize(Vector2f(500, 300));
    successBox.setFillColor(Color(50, 50, 50, 220)); // Dark gray, almost opaque
    successBox.setOutlineThickness(3);
    successBox.setOutlineColor(Color::White);
    
    // Setup texts
    setupText(&successTitle, mainFont, "SUCCESS!", 48, Color::Green);
    setupText(&successInstruction1, mainFont, "Press Enter to Continue", 24, Color::White);
    setupText(&successInstruction2, mainFont, "Press ESC to Quit", 20, Color(200, 200, 200));
}

void Engine::updateSuccessLevelPopupPosition(){
    Vector2f cameraCenter = camera.getCenter();
    Vector2f camSize = camera.getSize();
    successOverlay.setSize(camSize);
    successOverlay.setPosition(Vector2f(
        cameraCenter.x - (camSize.x / 2.0f),
        cameraCenter.y - (camSize.y / 2.0f)
    ));
    
    // Center the popup box
    Vector2f boxSize = successBox.getSize();
    successBox.setPosition(Vector2f(
        cameraCenter.x - (boxSize.x / 2.0f),
        cameraCenter.y - (boxSize.y / 2.0f)
    ));
    
    // Position texts inside the box
    FloatRect successTitleBounds = successTitle.getLocalBounds();
    successTitle.setPosition(Vector2f(
        cameraCenter.x - (successTitleBounds.size.x / 2.0f),
        cameraCenter.y - 80.0f
    ));
    
    FloatRect instruction1Bounds = successInstruction1.getLocalBounds();
    successInstruction1.setPosition(Vector2f(
        cameraCenter.x - (instruction1Bounds.size.x / 2.0f),
        cameraCenter.y + 10.0f
    ));
    
    FloatRect instruction2Bounds = successInstruction2.getLocalBounds();
    successInstruction2.setPosition(Vector2f(
        cameraCenter.x - (instruction2Bounds.size.x / 2.0f),
        cameraCenter.y + 50.0f
    ));
}

void Engine::drawSuccessLevelPopup(){
    // Update positions only once per frame
    updateSuccessLevelPopupPosition();
    
    // Draw overlay first (makes background transparent)
    window.draw(successOverlay);
    
    // Draw popup box
    window.draw(successBox);
    
    // Draw texts
    window.draw(successTitle);
    window.draw(successInstruction1);
    window.draw(successInstruction2);
    
    // Display everything at once to prevent flickering
    window.display();
}