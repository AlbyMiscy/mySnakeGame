#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace sf;
using namespace std;

struct GridProvider {
    virtual bool isBlocked( Vector2u) const = 0;
    virtual  Vector2u size() const = 0;
};

deque< Vector2u> astar(GridProvider const& g, Vector2u start,  Vector2u goal);
