#include "../headers/pathfinding.hpp"
#include <queue>
#include <unordered_map>
#include <cmath>

struct Node{ sf::Vector2u t; float g,f; };
struct KeyHash{ size_t operator()(sf::Vector2u v) const { return (v.x<<16) ^ v.y; } };
static float h(sf::Vector2u a, sf::Vector2u b){
    return std::abs((int)a.x-(int)b.x) + std::abs((int)a.y-(int)b.y);
}
std::deque<sf::Vector2u> astar(GridProvider const& g, sf::Vector2u s, sf::Vector2u goal){
    auto cmp=[](Node const&a, Node const&b){ return a.f>b.f; };
    std::priority_queue<Node,std::vector<Node>,decltype(cmp)> open(cmp);
    std::unordered_map<sf::Vector2u,float,KeyHash> gscore;
    std::unordered_map<sf::Vector2u,sf::Vector2u,KeyHash> came;

    gscore[s]=0; open.push({s,0,h(s,goal)});
    auto inside=[&](sf::Vector2u t){ return t.x<g.size().x && t.y<g.size().y; };

    const int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    while(!open.empty()){
        Node cur=open.top(); open.pop();
        if(cur.t==goal){
            std::deque<sf::Vector2u> path; sf::Vector2u p=goal;
            path.push_front(p);
            while(p!=s){ p=came[p]; path.push_front(p); }
            return path;
        }
        for(int k=0;k<4;++k){
            int nx=(int)cur.t.x+dx[k], ny=(int)cur.t.y+dy[k];
            if(nx<0||ny<0) continue;
            sf::Vector2u nt{(unsigned)nx,(unsigned)ny};
            if(!inside(nt) || g.isBlocked(nt)) continue;
            float tentative = gscore[cur.t] + 1.f;
            if(!gscore.count(nt) || tentative < gscore[nt]){
                gscore[nt]=tentative; came[nt]=cur.t;
                open.push({nt, tentative, tentative + h(nt,goal)});
            }
        }
    }
    return {};
}
