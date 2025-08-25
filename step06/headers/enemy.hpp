#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
class Enemy {
public:
    enum class TextureType { Enemy1, Enemy2 };
    Enemy(sf::Vector2u A, sf::Vector2u B, TextureType type = TextureType::Enemy1);
    void setPath(const std::deque<sf::Vector2u>& p);
    void update(float dt);
    void draw(sf::RenderTarget& rt) const;
    sf::FloatRect bounds() const;
    bool atEnd() const;
    void reverse();
    sf::Vector2u currentTile() const;
    static sf::Texture s_tex1, s_tex2;
    static bool s_loaded1, s_loaded2;
    TextureType m_type;
    std::unique_ptr<sf::Sprite> m_sprite;
    std::deque<sf::Vector2u> m_path;
    float m_speedPx = 80.f;
    sf::Vector2f m_posPx;
    size_t m_pathIdx = 0;
    void ensureTexture(TextureType type);

    // --- Animation ---
    int m_animFrame = 0;
    float m_animTimer = 0.f;
    static constexpr int ANIM_FRAMES = 5;
    static constexpr float ANIM_SPEED = 0.12f; // sec per frame
    bool m_forward = true; // true: A->B (row 0), false: B->A (row 1)
};
