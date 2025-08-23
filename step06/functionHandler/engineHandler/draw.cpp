#include "engine.hpp"

void Engine::draw(){
    window.clear(Color::Black);

    // Draw walls
    for(auto & w : wallSection){
        window.draw(w.getShape());
    }

    // Draw fruit section
    window.draw(fruit.getSprite());

    // Draw snake section
    for(auto & s : snake){
        window.draw(s.getShape());
    }

    // Draw nemici
    drawEnemies();

    // Draw Text
    window.draw(titleText);
    window.draw(currentLevelText);
    window.draw(fruitEatenText);
    
    // Draw direction arrow (only when fruit is outside camera view)
    drawDirectionArrow();
    
    // Draw Game Over text only when in GAMEOVER state
    if(currentGameState == GameState::GAMEOVER) {
        window.draw(gameOver);
        window.draw(pressEnterText);
    }

    // Only display if not in popup states (popup functions will handle display)
    if(currentGameState != GameState::PAUSED && currentGameState != GameState::LEVEL_SUCCESS) {
        window.display();
    }
}