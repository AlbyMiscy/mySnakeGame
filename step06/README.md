# 🐍 Step06 - Nemici, skin personalizzate e pathfinding avanzato

<img width="811" height="633" alt="image" src="https://github.com/user-attachments/assets/fb131991-0a04-4db8-b0ba-c9e180b66b84" />

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/a512432f-3a1f-4078-9845-5fdc883563ac" width="320" alt="enemy1"><br>
      <br><b>enemy 1</b>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/e6d65070-ec02-40a8-9fa2-13eba0bafcb6" width="320" alt="enemy2"><br>
     <br><b>enemy 2</b>
    </td>
  </tr>
</table>

## 📌 Descrizione

In questo step il progetto evolve rispetto a step05 con l'introduzione di:
- **Nemici e pathfinding**: nemici che si muovono autonomamente sulla mappa seguendo lo snake tramite algoritmo A* e causano il game over in caso di collisione.
- **Skin per lo snake**: aggiunta una skin per lo snake.
- **Gestione texture avanzata**: caricamento dinamico delle texture nemici e skin snake da cartelle dedicate.

## 🆕 Novità rispetto a Step05

| Funzionalità                | Step05                        | Step06 (questo step)                |
|-----------------------------|-------------------------------|-------------------------------------|
| Nemici                      | ❌ assenti                    | ✅ presenti con pathfinding          |
| Pathfinding                 | ❌                            | ✅ A* per inseguimento nemici        |
| Skin per lo snake           | ❌                            | ✅ caricamento dinamico da cartella  |
| Gestione texture nemici     | ❌                            | ✅ caricamento dinamico da cartella  |

## 🔧 Dettagli implementativi

### 👾 Nemici e pathfinding
- Aggiunta la classe `Enemy` che rappresenta i nemici sulla mappa.
- Ogni nemico utilizza l'algoritmo A* per calcolare il percorso più breve verso lo snake, evitando muri e ostacoli.
- Se un nemico collide con la testa dello snake, il gioco termina (game over).
- Le texture dei nemici sono caricate dinamicamente da `resources/texture/enemy/`.

### 🐍 Snake con skin
- Refactoring della classe `Snake` per supportare sprite sheet (testa/corpo, 4 direzioni).
- Caricamento dinamico della texture.
- Gestione della direzione e aggiornamento del rettangolo di texture per ogni segmento.

### 🎨 Gestione texture
- Le texture dei nemici e delle skin dello snake sono ora caricate da cartelle dedicate (`enemy/` e `skin/`).
- Possibilità di aggiungere facilmente nuove skin per i nemici semplicemente inserendo nuove immagini nella rispettiva cartella.

## ⭐ Algoritmo A* (A-star) per il pathfinding dei nemici

L'algoritmo A* è un algoritmo di ricerca del percorso ottimale molto utilizzato nei videogiochi per trovare la strada più breve tra due punti su una griglia, tenendo conto di ostacoli.

**Funzionamento di base:**
- Ogni cella della mappa è un nodo del grafo.
- Si mantiene una coda di priorità (open set) ordinata in base al costo stimato (f = g + h):
  - `g` = costo effettivo dal punto di partenza al nodo corrente
  - `h` = stima euristica (di solito distanza di Manhattan) dal nodo corrente al punto di arrivo
- Ad ogni iterazione si espande il nodo con costo f più basso, aggiungendo i vicini non bloccati.
- Il percorso viene ricostruito risalendo dai nodi finali a quelli iniziali tramite una mappa dei predecessori.

**Applicazione ai nemici:**
- Ogni nemico, ad ogni aggiornamento, calcola il percorso più breve verso la testa dello snake usando A*.
- Gli ostacoli (muri, altri nemici) sono considerati come celle bloccate.
- Il nemico si muove lungo il percorso calcolato, aggiornando la propria posizione ad ogni frame.
- Se la testa dello snake si trova nella stessa cella del nemico, viene attivato il game over.

**Vantaggi:**
- Permette ai nemici di "inseguire" lo snake in modo intelligente, evitando ostacoli e scegliendo sempre la strada più breve.
- L'algoritmo è efficiente e facilmente estendibile per mappe di dimensioni medio-grandi.

## 🗂️ Struttura aggiornata del progetto

```text
step06/
├── headers/
│   ├── engine.hpp                 # Engine principale, ora con gestione skin e nemici
│   ├── enemy.hpp                  # Definizione della classe Enemy
│   ├── fruit.hpp
│   ├── pathfinding.hpp            # Algoritmo A* e interfaccia GridProvider
│   ├── snake.hpp                  # Snake con supporto skin/sprite sheet
│   └── wall.hpp
├── src/
│   ├── engine.cpp
│   ├── enemy.cpp                  # Implementazione nemici e pathfinding
│   ├── fruit.cpp
│   ├── main.cpp
│   ├── pathfinding.cpp            # Implementazione A*
│   ├── snake.cpp                  # Snake con sprite e caricamento skin
│   └── wall.cpp
└── functionHandler/engineHandler/
    ├── cameraHandler.cpp
    ├── directionArrowHandler.cpp
    ├── draw.cpp                   # Rendering snake con sprite
    ├── fruitHandler.cpp
    ├── input.cpp                  # Input e gestione skin
    ├── levelHandler.cpp
    ├── snakeHandler.cpp           # Creazione snake con skin
    ├── textHandler.cpp            
    ├── togglePauseHandler.cpp
    └── update.cpp
```

## ✅ Risultato
- Il gioco ora include nemici con pathfinding e collisioni.
- Lo snake ha una skin di default e può essere facilmente esteso con nuove skin.

## 🎮 Controlli
- **ENTER**: Avvia il gioco / conferma nei popup
- **ESC**: Esci dal gioco / torna al menu
- **Frecce direzionali**: Muovi lo snake
- **P**: Pausa/Resume

## 🏗️ Build ed esecuzione
### Build Standard
```bash
# Configurazione (genera anche compile_commands.json per VS Code)
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Compilazione con copia automatica resources/
cmake --build build -j

# Esecuzione - ENTRAMBI i modi funzionano!
./step06                # Dalla directory build/
# OPPURE  
./build/step06          # Dalla directory principale
```