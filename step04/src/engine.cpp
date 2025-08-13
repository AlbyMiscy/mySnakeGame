#include "engine.hpp"

const Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() : mainFont([]() { 
    Font f; 
    if (!f.openFromFile("resources/fonts/A_Goblin_Appears.otf")) {
        std::cerr << "Warning: Could not load custom font, using default" << std::endl;
    }
    return f; 
}()), titleText(mainFont), currentLevelText(mainFont), fruitEatenText(mainFont), gameOver(mainFont), pressEnterText(mainFont) {
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", sf::Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();
    startGame();
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

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER){
            input();
            if(currentGameState == GameState::GAMEOVER){
                draw();
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

