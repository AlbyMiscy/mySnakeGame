#include "pathfinding.hpp"

struct Node{  Vector2u t; float g,f; };
struct KeyHash{ size_t operator()( Vector2u v) const { return (v.x<<16) ^ v.y; } };
static float h( Vector2u a,  Vector2u b){
    return  abs((int)a.x-(int)b.x) +  abs((int)a.y-(int)b.y);
}
 deque< Vector2u> astar(GridProvider const& g,  Vector2u s,  Vector2u goal){
    auto cmp=[](Node const&a, Node const&b){ return a.f>b.f; };
    priority_queue<Node, vector<Node>,decltype(cmp)> open(cmp);
    unordered_map< Vector2u,float,KeyHash> gscore;
    unordered_map< Vector2u, Vector2u,KeyHash> came;

    gscore[s]=0; open.push({s,0,h(s,goal)});
    auto inside=[&]( Vector2u t){ return t.x<g.size().x && t.y<g.size().y; };

    const int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    while(!open.empty()){
        Node cur=open.top(); open.pop();
        if(cur.t==goal){
             deque< Vector2u> path;  Vector2u p=goal;
            path.push_front(p);
            while(p!=s){ p=came[p]; path.push_front(p); }
            return path;
        }
        for(int k=0;k<4;++k){
            int nx=(int)cur.t.x+dx[k], ny=(int)cur.t.y+dy[k];
            if(nx<0||ny<0) continue;
             Vector2u nt{(unsigned)nx,(unsigned)ny};
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
