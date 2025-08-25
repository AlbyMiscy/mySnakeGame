#include "engine.hpp"

void Engine::moveFruit(){
    // find a location to place the fruit
    // must not be inside the snake, or the wall

    // Use the map size instead of the window size
    sf::Vector2f fruitResolution(
    static_cast<float>(mapSize.x) - 2.f,  // -2 to avoid the borders
        static_cast<float>(mapSize.y) - 2.f
    );
    Vector2f newFruitLocation;
    bool badLocation = false;
    srand(time(nullptr));
    do {
        badLocation = false;
    // Generate a random position in the whole map
        newFruitLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)fruitResolution.x)) * 20;
        newFruitLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)fruitResolution.y)) * 20;

        const sf::FloatRect fruitRect({newFruitLocation.x, newFruitLocation.y},
                                    {20.f, 20.f});

        // Check if it is in the snake
        for(auto & s : snake){
            const sf::FloatRect snakeBounds = s.getSprite().getGlobalBounds();
        
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
    fruit.randomizeSprite(); // Randomize sprite when fruit moves to new position
}