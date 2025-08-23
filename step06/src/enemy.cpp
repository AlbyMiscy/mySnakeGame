#include "../headers/enemy.hpp"
#include <algorithm>
#include <cmath>
using namespace sf;

sf::Texture Enemy::s_tex; bool Enemy::s_loaded=false;

Enemy::Enemy(Vector2u A, Vector2u B){
    ensureTexture();
    m_sprite = std::make_unique<sf::Sprite>(s_tex);
    m_sprite->setScale({1.25f,1.25f});
    m_posPx = Vector2f(A.x*20.f, A.y*20.f);
    m_sprite->setPosition(m_posPx);
}

void Enemy::ensureTexture(){
    if(!s_loaded){
        s_tex.loadFromFile("resources/texture/enemy.png");
        s_loaded=true;
    }
}

void Enemy::setPath(const std::deque<Vector2u>& p){ m_path = p; m_pathIdx=0; }

void Enemy::update(float dt){
    if (m_path.empty() || m_pathIdx>=m_path.size()) return;
    Vector2f target(m_path[m_pathIdx].x*20.f, m_path[m_pathIdx].y*20.f);
    Vector2f d = target - m_posPx;
    float len = std::sqrt(d.x*d.x + d.y*d.y);
    if (len < 1.f){
        m_posPx = target;
        m_pathIdx++;
    } else {
        Vector2f dir = d / len;
        m_posPx += dir * (m_speedPx * dt);
    }
    m_sprite->setPosition(m_posPx);
}

void Enemy::draw(RenderTarget& rt) const { rt.draw(*m_sprite); }
FloatRect Enemy::bounds() const { return m_sprite->getGlobalBounds(); }
bool Enemy::atEnd() const { return m_pathIdx>=m_path.size(); }
void Enemy::reverse(){ std::reverse(m_path.begin(), m_path.end()); m_pathIdx=0; }
Vector2u Enemy::currentTile() const { return Vector2u( (unsigned)(m_posPx.x/20), (unsigned)(m_posPx.y/20) ); }
