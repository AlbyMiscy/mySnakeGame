#include "engine.hpp"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine(){
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake", sf::Style::Default);
    window.setFramerateLimit(FPS);

    speed = 4;
    snakeDirection = Direction::RIGHT;

    timeSinceLastMove = Time::Zero;

    newSnake();
}

void Engine::run(){
    Clock clock;

    // main loop - Runs until the window is closed
    while(window.isOpen()){
        Time dt = clock.restart();
        timeSinceLastMove += dt;

        input();
        update();
        draw();
    }
}