#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

class Enemy {
public:
    enum class TextureType { Enemy1, Enemy2 };
    Enemy( Vector2u A,  Vector2u B, TextureType type = TextureType::Enemy1);
    void setPath(const deque< Vector2u>& p);
    void update(float dt);
    void draw( RenderTarget& rt) const;
    FloatRect bounds() const;
    bool atEnd() const;
    void reverse();
    Vector2u currentTile() const;
    static  Texture s_tex1, s_tex2;
    static bool s_loaded1, s_loaded2;
    TextureType m_type;
    unique_ptr< Sprite> m_sprite;
    deque< Vector2u> m_path;
    float m_speedPx = 80.f;
    Vector2f m_posPx;
    size_t m_pathIdx = 0;
    void ensureTexture(TextureType type);

    // Animation
    int m_animFrame = 0;
    float m_animTimer = 0.f;
    static constexpr int ANIM_FRAMES = 5;
    static constexpr float ANIM_SPEED = 0.12f; // sec per frame
    bool m_forward = true; // true: A->B (row 0), false: B->A (row 1)
};
