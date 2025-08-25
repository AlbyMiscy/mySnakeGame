#pragma once
#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>
struct GridProvider {
    virtual bool isBlocked(sf::Vector2u) const = 0;
    virtual sf::Vector2u size() const = 0;
};
std::deque<sf::Vector2u> astar(GridProvider const& g,
                               sf::Vector2u start, sf::Vector2u goal);
