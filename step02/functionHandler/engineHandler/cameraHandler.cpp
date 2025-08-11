#include "engine.hpp"

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
        
        // Fattore di smoothing (0.1 = movimento lento e fluido, 1.0 = movimento istantaneo)
        float smoothFactor = 0.15f;
        Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;
        
        camera.setCenter(newCenter);
        window.setView(camera);
    }
}
