#include "engine.hpp"

void Engine::initializeCamera() {
    // Imposta la camera in base alla dimensione attuale della finestra
    Vector2f winSize(window.getSize());
    camera.setSize(winSize);
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
        float smoothFactor = 0.08f;
        Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * smoothFactor;
        Vector2f camSize = camera.getSize();
        float halfWidth = camSize.x / 2.0f;
        float halfHeight = camSize.y / 2.0f;
        float mapWidthPixels = mapSize.x * 20.0f;
        float mapHeightPixels = mapSize.y * 20.0f;
        newCenter.x = std::max(halfWidth, std::min(newCenter.x, mapWidthPixels - halfWidth));
        newCenter.y = std::max(halfHeight, std::min(newCenter.y, mapHeightPixels - halfHeight));
        camera.setCenter(newCenter);
        window.setView(camera);
        updateTextPosition();
    }
}