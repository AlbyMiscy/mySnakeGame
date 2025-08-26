#include "engine.hpp"

const Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine(){
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();
    startGame();
}

void Engine::startGame(){
    speed = 4;
    snakeDirection = Direction::RIGHT;
    timeSinceLastMove = Time::Zero;
    sectionToAdd = 0;
    direction.clear();
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    initializeCamera(); // Initialize camera after snake's creation
    moveFruit();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;
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
        updateCamera(); // Update the camera every frame for smoother movement
        draw();
    }
}

void Engine::initializeCamera() {
    camera.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    
    // Centra la telecamera sulla posizione iniziale dello snake
    if (!snake.empty()) {
        camera.setCenter(snake[0].getPosition());
    } else {
        camera.setCenter(snakeStartPosition);
    }
    
    // Apply the view to the window
    window.setView(camera);
}

void Engine::updateCamera() {
    if (!snake.empty()) {
        Vector2f snakeHeadPosition = snake[0].getPosition();
        
        Vector2f centerPosition = snakeHeadPosition + Vector2f(10.f, 10.f);
        
        Vector2f currentCenter = camera.getCenter();
        Vector2f targetCenter = centerPosition;
        
        float smoothFactor = 0.08f; 
        Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;
        
        float halfWidth = WINDOW_WIDTH / 2.0f;
        float halfHeight = WINDOW_HEIGHT / 2.0f;
        
        float mapWidthPixels = mapSize.x * 20.0f;
        float mapHeightPixels = mapSize.y * 20.0f;
        
        newCenter.x = max(halfWidth, min(newCenter.x, mapWidthPixels - halfWidth));
        newCenter.y = max(halfHeight, min(newCenter.y, mapHeightPixels - halfHeight));
        
        camera.setCenter(newCenter);
        window.setView(camera);
    }
}