#include "engine.hpp"

void Engine::input() {
    window.handleEvents(
        [this](const sf::Event::Closed&) {
            window.close();
        },

        [this](const sf::Event::KeyPressed& e) {
            if (currentGameState == GameState::GAMEOVER) {
                if (e.scancode == sf::Keyboard::Scancode::Enter) {
                    startGame();
                }
            }

            switch (e.scancode) {
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    return;

                case sf::Keyboard::Scancode::P:
                    togglePause();
                    break;

                case sf::Keyboard::Scancode::Up:
                    addDirection(Direction::UP);
                    break;

                case sf::Keyboard::Scancode::Down:
                    addDirection(Direction::DOWN);
                    break;

                case sf::Keyboard::Scancode::Left:
                    addDirection(Direction::LEFT);
                    break;

                case sf::Keyboard::Scancode::Right:
                    addDirection(Direction::RIGHT);
                    break;

                default:
                    break;
            }
        }
    );
}

void Engine::addDirection(int newDirection){
    if(direction.empty()){
        direction.emplace_back(newDirection);
    }
    else{
        if(direction.back() != newDirection){
            direction.emplace_back(newDirection);
        }
    }
}