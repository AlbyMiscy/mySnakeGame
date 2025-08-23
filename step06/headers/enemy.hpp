#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
class Enemy {
public:
    Enemy(sf::Vector2u A, sf::Vector2u B);
    void setPath(const std::deque<sf::Vector2u>& p);
    void update(float dt);
    void draw(sf::RenderTarget& rt) const;
    sf::FloatRect bounds() const;
    bool atEnd() const;
    void reverse();
    sf::Vector2u currentTile() const;
private:
    static sf::Texture s_tex;
    static bool s_loaded;
    std::unique_ptr<sf::Sprite> m_sprite;
    std::deque<sf::Vector2u> m_path;
    float m_speedPx = 80.f;
    sf::Vector2f m_posPx;
    size_t m_pathIdx = 0;
    void ensureTexture();
};
