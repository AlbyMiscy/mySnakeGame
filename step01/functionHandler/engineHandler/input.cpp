#include "engine.hpp"

void Engine::input(){
    window.handleEvents(
            [this](const sf::Event::Closed&){
                window.close();
            },
            [this](const sf::Event::KeyPressed& e) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                    window.close();
                }
            }
        );
}