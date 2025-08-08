#include "engine.hpp"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine(){
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", sf::Style::Default);
    window.setFramerateLimit(FPS);
    newSnake();
}

void Engine::run(){
    // main loop - Runs until the window is closed
    while(window.isOpen()){
        input();
        draw();
    }
}