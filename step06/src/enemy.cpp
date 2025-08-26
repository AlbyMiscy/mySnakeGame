#include "../headers/enemy.hpp"

Texture Enemy::s_tex1;
Texture Enemy::s_tex2;
bool Enemy::s_loaded1 = false;
bool Enemy::s_loaded2 = false;

Enemy::Enemy(Vector2u A, Vector2u B, TextureType type)
    : m_type(type)
{
    ensureTexture(type);
    Texture& tex = (type == TextureType::Enemy1) ? s_tex1 : s_tex2;
    m_sprite = make_unique<Sprite>(tex, IntRect({0,0}, {20,20}));
    m_sprite->setScale({1.25f,1.25f});
    m_posPx = Vector2f(A.x*20.f, A.y*20.f);
    m_sprite->setPosition(m_posPx);
    m_animFrame = 0;
    m_animTimer = 0.f;
    m_forward = true;
}

void Enemy::ensureTexture(TextureType type){
    if(type == TextureType::Enemy1 && !s_loaded1){
    if (!s_tex1.loadFromFile("resources/texture/enemy/enemy1.png")) {
            cerr << "Error: unable to load enemy1.png" << endl;
        }
        s_loaded1 = true;
    }
    if(type == TextureType::Enemy2 && !s_loaded2){
    if (!s_tex2.loadFromFile("resources/texture/enemy/enemy2.png")) {
            cerr << "Error: unable to load enemy2.png" << endl;
        }
        s_loaded2 = true;
    }
}

void Enemy::setPath(const deque<Vector2u>& p){ m_path = p; m_pathIdx=0; }

void Enemy::update(float dt){
    if (m_path.empty() || m_pathIdx>=m_path.size()) return;
    Vector2f target(m_path[m_pathIdx].x*20.f, m_path[m_pathIdx].y*20.f);
    Vector2f d = target - m_posPx;
    float len = sqrt(d.x*d.x + d.y*d.y);
    if (len < 1.f){
        m_posPx = target;
        m_pathIdx++;
    } else {
        Vector2f dir = d / len;
        m_posPx += dir * (m_speedPx * dt);
    }
    m_sprite->setPosition(m_posPx);

    // Bidirectional sprite sheet animation
    m_animTimer += dt;
    if(m_animTimer >= ANIM_SPEED){
        m_animTimer -= ANIM_SPEED;
        m_animFrame = (m_animFrame+1)%ANIM_FRAMES;
    }
    int yrow = m_forward ? 0 : 20;
    m_sprite->setTextureRect(IntRect({m_animFrame*20, yrow}, {20,20}));
}

void Enemy::draw(RenderTarget& rt) const { rt.draw(*m_sprite); }

FloatRect Enemy::bounds() const { return m_sprite->getGlobalBounds(); }

bool Enemy::atEnd() const { return m_pathIdx>=m_path.size(); }

void Enemy::reverse(){
    std::reverse(m_path.begin(), m_path.end());
    m_pathIdx=0;
    m_forward = !m_forward;
}

Vector2u Enemy::currentTile() const { return Vector2u( (unsigned)(m_posPx.x/20), (unsigned)(m_posPx.y/20) ); }
