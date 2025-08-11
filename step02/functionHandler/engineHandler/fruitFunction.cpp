#include "engine.hpp"

void Engine::moveFruit(){
    // find a location to place the fruit
    // must not be inside the snake, or the wall

    // Usa le dimensioni della mappa invece delle dimensioni della finestra
    sf::Vector2f fruitResolution(
        static_cast<float>(mapSize.x) - 2.f,  // -2 per evitare i bordi
        static_cast<float>(mapSize.y) - 2.f
    );
    Vector2f newFruitLocation;
    bool badLocation = false;
    srand(time(nullptr));
    do {
        badLocation = false;
        // Genera posizione casuale nell'intera mappa
        newFruitLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)fruitResolution.x)) * 20;
        newFruitLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)fruitResolution.y)) * 20;

        const sf::FloatRect fruitRect({newFruitLocation.x, newFruitLocation.y},
                                    {20.f, 20.f});

        // Check if it is in the snake
        for(auto & s : snake){
            const sf::FloatRect snakeBounds = s.getShape().getGlobalBounds();
        
            if(snakeBounds.findIntersection(fruitRect)){
                badLocation = true;
                break;
            }
        }

        // Check if it is in the walls
        for(auto & w : wallSection){
            if(w.getShape().getGlobalBounds().findIntersection(fruitRect)){
                badLocation = true;
                break;
            }
        }
    }
    while (badLocation);
    fruit.setPosition(newFruitLocation);
}