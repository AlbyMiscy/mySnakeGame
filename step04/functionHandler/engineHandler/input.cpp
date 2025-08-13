#include "engine.hpp"

void Engine::input() {
    window.handleEvents(
        [this](const sf::Event::Closed&) {
            window.close();
        },

        [this](const sf::Event::KeyPressed& e) {
            // Menu input handling
            if (currentGameState == GameState::MENU) {
                if (e.scancode == sf::Keyboard::Scancode::Enter) {
                    startGame(); // Start the game
                    return;
                }
                if (e.scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                    return;
                }
            }
            
            // Game Over input handling
            if (currentGameState == GameState::GAMEOVER) {
                if (e.scancode == sf::Keyboard::Scancode::Enter) {
                    startGame();
                    return;
                }
            }

            // General game controls
            switch (e.scancode) {
                case sf::Keyboard::Scancode::Escape:
                    if (currentGameState == GameState::RUNNING) {
                        currentGameState = GameState::MENU; // Return to menu
                    } else {
                        window.close();
                    }
                    return;

                case sf::Keyboard::Scancode::P:
                    if (currentGameState == GameState::RUNNING || currentGameState == GameState::PAUSED) {
                        togglePause();
                    }
                    break;

                case sf::Keyboard::Scancode::Up:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::UP);
                    }
                    break;

                case sf::Keyboard::Scancode::Down:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::DOWN);
                    }
                    break;

                case sf::Keyboard::Scancode::Left:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::LEFT);
                    }
                    break;

                case sf::Keyboard::Scancode::Right:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::RIGHT);
                    }
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