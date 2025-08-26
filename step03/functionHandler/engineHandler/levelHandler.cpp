#include "engine.hpp"


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
    // Bounds check to avoid segmentation fault
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
    
    const  Color BLACK  =  Color(0, 0, 0);
    const  Color RED    =  Color(255, 0, 0);
    const  Color BLUE   =  Color(0, 0, 255);

    constexpr float TILE = 20.f;

    for (unsigned y = 0; y < size.y; ++y) {
        for (unsigned x = 0; x < size.x; ++x) {
            const  Color c = img.getPixel({x, y});
             Vector2f pos(x * TILE, y * TILE);
            if (c == BLACK) {
                wallSection.emplace_back(Wall(pos, {TILE, TILE}));
            } else if (c == RED) {
                snakeStartPosition = pos;
            }
        }
    }
}