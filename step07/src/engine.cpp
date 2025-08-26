
#include "engine.hpp"

bool Engine::isBlocked(Vector2u t) const {
    if (t.x >= mapSize.x || t.y >= mapSize.y) return true;
     Rect<float> cell({t.x*20.f, t.y*20.f}, {20.f, 20.f});
    for (const auto& w : wallSection){
        if (w.getShape().getGlobalBounds().findIntersection(cell)) return true;
    }
    return false;
}

void Engine::updateEnemies(float dt){
    for (auto& e : enemies) {
        e.update(dt);
    // collision with snake head
    if (e.bounds().findIntersection(snake[0].getSprite().getGlobalBounds()).has_value()) {
            currentGameState = GameState::GAMEOVER;
        }
    // patrol A→B→A (once arrived, reverse)
        if (e.atEnd()) e.reverse();
    }
}

void Engine::drawEnemies(){
    for (auto& e : enemies) e.draw(window);
}

const Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() : mainFont([]() { 
    Font f; 
    if (!f.openFromFile("resources/fonts/A_Goblin_Appears.otf")) {
        std::cerr << "Warning: Could not load custom font, using default" << std::endl;
    }
    return f; 
}()), titleText(mainFont), currentLevelText(mainFont), fruitEatenText(mainFont), gameOver(mainFont), pressEnterText(mainFont), menuTitle(mainFont), playText(mainFont), quitText(mainFont), instructionsText(mainFont), pauseTitle(mainFont), pauseInstruction1(mainFont), pauseInstruction2(mainFont),
      successTitle(mainFont), successInstruction1(mainFont), successInstruction2(mainFont), arrowSprite(arrowTexture), currentArrowFrame(0), arrowAnimationTimer(Time::Zero) {
    window.create( VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake",  Style::Default);
    window.setFramerateLimit(FPS);
    window.setVerticalSyncEnabled(true); // Enable VSync to reduce tearing/glitches
    maxLevels = 0;
    checkLevelFiles();
    currentGameState = GameState::MENU; // Start with menu
    setupMenu();
    setupSuccessLevelPopup();
    setupPausePopup(); // Setup pause popup elements
    setupDirectionArrow(); // Setup direction arrow
    fixText(); 
}

void Engine::startGame(){

    speed = 4;
    snakeDirection = Direction::RIGHT;
    timeSinceLastMove = Time::Zero;
    sectionToAdd = 0;
    direction.clear();
    wallSection.clear();
    fruitEatenThisLevel = 0;
    fruitEatenTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    initializeCamera(); 
    moveFruit();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;
    updateTextContent(); // Update text's content with start values
}

void Engine::run(){
    Clock clock;

    // main loop - Runs until the window is closed
    while(window.isOpen()){
        Time dt = clock.restart();

        if(currentGameState == GameState::MENU) {
            input();
            drawMenu();
            sleep(milliseconds(2));
            continue;
        }

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER || currentGameState == GameState::LEVEL_SUCCESS){
            input();
            if(currentGameState == GameState::GAMEOVER){
                draw();
                window.display(); // Ensure display is called for game over
            } else if(currentGameState == GameState::PAUSED) {
                draw(); // Draw normal game first
                drawPausePopup(); // Draw pause popup on top (includes display)
            }
            else if(currentGameState == GameState::LEVEL_SUCCESS){
                draw(); // Draw normal game first  
                drawSuccessLevelPopup(); // Draw success popup on top (includes display)
            }

            // Reduce CPU usage during popup states
            sleep(milliseconds(16)); // ~60 FPS equivalent
            continue;
        }

        timeSinceLastMove += dt;

        input();
        update();
        updateCamera(); 
        draw();
    }
}

