#include "engine.hpp"

void Engine::input() {
    window.handleEvents(
        [this](const Event::Closed&) {
            window.close();
        },

        [this](const Event::Resized& e) {
            // Update camera and overlay/texts when the window is resized
            camera.setSize(Vector2f(static_cast<float>(e.size.x), static_cast<float>(e.size.y)));
            window.setView(camera);
            updateTextPosition();
            updatePausePopupPosition();
            updateSuccessLevelPopupPosition();
        },

        [this](const Event::KeyPressed& e) {
            // Menu input handling
            if (currentGameState == GameState::MENU) {
                if (e.scancode == Keyboard::Scancode::Enter) {
                    startGame(); // Start the game
                    return;
                }
                if (e.scancode == Keyboard::Scancode::Escape) {
                    window.close();
                    return;
                }
            }
            
            // Game Over input handling
            if (currentGameState == GameState::GAMEOVER) {
                if (e.scancode == Keyboard::Scancode::Enter) {
                    startGame();
                    return;
                }
            }

            // Level Success input handling
            if (currentGameState == GameState::LEVEL_SUCCESS) {
                if (e.scancode == Keyboard::Scancode::Enter) {
                    // Continue to next level
                    beginNextLevel();
                    currentGameState = GameState::RUNNING;
                    return;
                }
                if (e.scancode == Keyboard::Scancode::Escape) {
                    currentGameState = GameState::MENU;
                    return;
                }
            }

            // General game controls
            switch (e.scancode) {
                case Keyboard::Scancode::Escape:
                    if (currentGameState == GameState::RUNNING) {
                        currentGameState = GameState::MENU; // Return to menu
                    } else {
                        window.close();
                    }
                    return;

                case Keyboard::Scancode::P:
                    if (currentGameState == GameState::RUNNING || currentGameState == GameState::PAUSED) {
                        togglePause();
                    }
                    break;

                case Keyboard::Scancode::Up:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::UP);
                    }
                    break;

                case Keyboard::Scancode::Down:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::DOWN);
                    }
                    break;

                case Keyboard::Scancode::Left:
                    if (currentGameState == GameState::RUNNING) {
                        addDirection(Direction::LEFT);
                    }
                    break;

                case Keyboard::Scancode::Right:
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