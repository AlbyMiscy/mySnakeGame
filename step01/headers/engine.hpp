#ifndef SNAKE_ENGINE_HPP
#define SNAKE_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;
using namespace std;

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

class Engine {
private:
    // Window
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

public:
    Engine();

    void input(); 
    
    void draw();

    // main loop
    void run();
};

#endif //SNAKE_ENGINE_HPP