#include "engine.hpp"

void Engine::initializeCamera() {

    camera.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    
    if (!snake.empty()) {
        camera.setCenter(snake[0].getPosition());
    } else {
        camera.setCenter(snakeStartPosition);
    }
    
    window.setView(camera);
    
    updateTextPosition();
}

void Engine::updateCamera() {
    if (!snake.empty()) {
        Vector2f snakeHeadPosition = snake[0].getPosition();
        
        Vector2f centerPosition = snakeHeadPosition + Vector2f(10.f, 10.f);
        
        Vector2f currentCenter = camera.getCenter();
        Vector2f targetCenter = centerPosition;
        
        float smoothFactor = 0.08f;  // Più basso = più fluido
        Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;
        
        float halfWidth = WINDOW_WIDTH / 2.0f;
        float halfHeight = WINDOW_HEIGHT / 2.0f;
        
        float mapWidthPixels = mapSize.x * 20.0f;
        float mapHeightPixels = mapSize.y * 20.0f;
        
        newCenter.x = std::max(halfWidth, std::min(newCenter.x, mapWidthPixels - halfWidth));
        newCenter.y = std::max(halfHeight, std::min(newCenter.y, mapHeightPixels - halfHeight));
        
        camera.setCenter(newCenter);
        window.setView(camera);
        
        updateTextPosition();
    }
}