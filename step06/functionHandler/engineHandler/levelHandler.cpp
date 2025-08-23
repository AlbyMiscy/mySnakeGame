#include "engine.hpp"
#include <iostream>

using namespace std;

void Engine::checkLevelFiles(){
    ifstream levelsManifest("resources/levels/levels.txt");
    if (!levelsManifest.is_open()) {
        cout << "Errore: impossibile aprire resources/levels/levels.txt" << endl;
        return;
    }
    
    ifstream testFile;
    for(string manifestLine; getline(levelsManifest, manifestLine);){
        testFile.open("resources/levels/" + manifestLine);
        if(testFile.is_open()){
            levels.emplace_back("resources/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

void Engine::loadLevel(int levelNumber){
    // Controllo bounds per evitare segmentation fault
    if (levelNumber < 1 || levelNumber > (int)levels.size()) {
        cout << "Errore: levelNumber fuori dai limiti. levelNumber=" << levelNumber 
             << ", levels.size()=" << levels.size() << endl;
        return;
    }

    Image img;
    string levelFile = levels[levelNumber - 1];
    
    if(!img.loadFromFile(levelFile)){
        cout << "Errore: impossibile caricare il file " << levelFile << endl;
        return; // error to load the file
    }

    wallSection.clear();

    const auto size = img.getSize(); 
    mapSize = size; 

    const sf::Color BLACK  = sf::Color(0, 0, 0);
    const sf::Color RED    = sf::Color(255, 0, 0);
    const sf::Color YELLOW = sf::Color(255,255,0);
    const sf::Color GREEN  = sf::Color(0,255,0);

    constexpr float TILE = 20.f;

    std::vector<sf::Vector2u> patrolA, patrolB;

    for (unsigned y = 0; y < size.y; ++y) {
        for (unsigned x = 0; x < size.x; ++x) {
            const sf::Color c = img.getPixel({x, y});
            sf::Vector2f pos(x * TILE, y * TILE);
            if (c == BLACK) {
                wallSection.emplace_back(Wall(pos, {TILE, TILE}));
            } else if (c == RED) {
                snakeStartPosition = pos;
            } else if (c == YELLOW) {
                patrolA.emplace_back(sf::Vector2u{x, y});
            } else if (c == GREEN) {
                patrolB.emplace_back(sf::Vector2u{x, y});
            }
        }
    }

    // Pairing semplice: in ordine di raccolta
    size_t n = std::min(patrolA.size(), patrolB.size());
    enemies.clear();
    for(size_t i=0;i<n;++i){
        Enemy::TextureType type = (i % 2 == 0) ? Enemy::TextureType::Enemy1 : Enemy::TextureType::Enemy2;
        enemies.emplace_back( Enemy(patrolA[i], patrolB[i], type) );
    }
    // Calcolo path per ogni enemy:
    MyGrid g(this);
    for(size_t i=0;i<enemies.size();++i){
        auto path = astar(g, patrolA[i], patrolB[i]);
        if(!path.empty()) enemies[i].setPath(path);
    }
}

void Engine::beginNextLevel(){
    currentLevel += 1;
    wallSection.clear();
    direction.clear();
    speed = 2 + currentLevel;
    snakeDirection = Direction::RIGHT;
    sectionToAdd = 0;
    sectionToAdd = 0;
    fruitEatenThisLevel = 0;

    loadLevel(currentLevel);
    newSnake();
    moveFruit();
    updateTextContent();
}