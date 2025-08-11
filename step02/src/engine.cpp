#include "engine.hpp"
#include <algorithm>  // Per std::max e std::min

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine(){
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", sf::Style::Default);
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
    initializeCamera(); // Inizializza la telecamera dopo aver creato lo snake
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
        updateCamera(); // Aggiorna la telecamera ogni frame per maggiore fluidità
        draw();
    }
}

void Engine::initializeCamera() {
    // Inizializza la telecamera con le dimensioni della finestra
    camera.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    
    // Centra la telecamera sulla posizione iniziale dello snake
    if (!snake.empty()) {
        camera.setCenter(snake[0].getPosition());
    } else {
        camera.setCenter(snakeStartPosition);
    }
    
    // Applica la view alla finestra
    window.setView(camera);
}

void Engine::updateCamera() {
    if (!snake.empty()) {
        // Ottieni la posizione della testa dello snake
        Vector2f snakeHeadPosition = snake[0].getPosition();
        
        // Aggiusta la posizione per centrare sulla tile (aggiunge metà tile)
        Vector2f centerPosition = snakeHeadPosition + Vector2f(10.f, 10.f);
        
        // Smooth camera movement - interpolazione per movimento fluido
        Vector2f currentCenter = camera.getCenter();
        Vector2f targetCenter = centerPosition;
        
        // Fattore di smoothing aumentato per maggiore fluidità
        float smoothFactor = 0.08f;  // Più basso = più fluido
        Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;
        
        // **LIMITI DELLA MAPPA** - Calcola i confini per evitare di vedere oltre la mappa
        float halfWidth = WINDOW_WIDTH / 2.0f;
        float halfHeight = WINDOW_HEIGHT / 2.0f;
        
        // Dimensioni mappa in pixel (mapSize è in pixel dell'immagine, moltiplicato per 20 per tile size)
        float mapWidthPixels = mapSize.x * 20.0f;
        float mapHeightPixels = mapSize.y * 20.0f;
        
        // Limita la telecamera ai confini della mappa
        newCenter.x = std::max(halfWidth, std::min(newCenter.x, mapWidthPixels - halfWidth));
        newCenter.y = std::max(halfHeight, std::min(newCenter.y, mapHeightPixels - halfHeight));
        
        camera.setCenter(newCenter);
        window.setView(camera);
    }
}