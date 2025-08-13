#include "engine.hpp"

const Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() : mainFont([]() { 
    Font f; 
    if (!f.openFromFile("resources/fonts/A_Goblin_Appears.otf")) {
        std::cerr << "Warning: Could not load custom font, using default" << std::endl;
    }
    return f; 
}()), titleText(mainFont), currentLevelText(mainFont), fruitEatenText(mainFont), gameOver(mainFont), pressEnterText(mainFont), menuTitle(mainFont), playText(mainFont), quitText(mainFont), instructionsText(mainFont), pauseTitle(mainFont), pauseInstruction1(mainFont), pauseInstruction2(mainFont) {
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", sf::Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();
    currentGameState = GameState::MENU; // Start with menu
    setupMenu();
    setupPausePopup(); // Setup pause popup elements
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

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER){
            input();
            if(currentGameState == GameState::GAMEOVER){
                draw();
            } else if(currentGameState == GameState::PAUSED) {
                draw(); // Draw normal game with transparency effect
                drawPausePopup(); // Draw pause popup on top
            }

            sleep(milliseconds(2)); // sleep so we don't peg the CPU
            continue;
        }

        timeSinceLastMove += dt;

        input();
        update();
        updateCamera(); 
        draw();
    }
}

