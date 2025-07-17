# CandyMatch – C++ Match-3 Game with Goals

A modern C++ implementation of a **Candy Crush-style** match-3 game, featuring a graphical interface, level goals, and progressive difficulty.  
Built on the same engine concepts as our Tetris clone, but centered on swapping candies to fulfill level objectives.

---

## Features

- **8×8 Candy Grid**  
  Real-time rendering of a grid filled with colorful candy tiles

- **Match-3 Mechanics**  
  - Swap adjacent candies horizontally or vertically  
  - Automatic detection and removal of any 3+ aligned candies  
  - Chain reactions (cascades) when new matches form
  - You must complete the objective in 10 moves

- **Level Goals**  
  Each level defines a target candy type and count (e.g., “eat 20 red candies”)  
  Progress is tracked on-screen until you reach your goal

- **Score & Progression**  
  - Points awarded per candy cleared, with bonuses for cascades  
  - Move limit per level to increase challenge  

- **Power-ups & Special Candies**  
  Create striped, wrapped, or color-bomb candies by matching 4+ in special patterns
  Activate them to clear rows, columns, or all candies of one color

- **Persistent High Scores**  
  Stores your best scores per level in a local file

---

## Controls

<div align="center">

| Input          | Action                                |
|----------------|---------------------------------------|
| Left Click     | Select first candy                    |
| Left Click     | Select second candy to swap           |
| `Esc`          | Exit the game                         |

</div>

---

## Class Structure

<div align="center">

| Class       | Responsibility                                         |
|-------------|--------------------------------------------------------|
| `Tetris`    | Main application and menu system                       |
| `Partida`   | Manages the gameplay session, goal tracking, move count |
| `Tauler`    | Board logic: candy grid, swaps, and state updates      |
| `Figura`    | Candy representation and logic (color/type)            |
| `InfoJoc`   | Shared enums, constants, and game configuration        |

</div>

---

## Build & Run

### Requirements

- C++11 or newer  
- SDL2 (or equivalent)  
- CMake or Make  

---

## Screenshots

### In-Game (Start of the Level)

<div align="center">
  <img width="737" height="821" alt="Captura de pantalla 2025-07-17 160919" src="https://github.com/user-attachments/assets/54159e97-f186-4424-ae09-1218b454573a" />
</div>

---

### In-Game (Objective Completed)

<div align="center">
  <img width="732" height="859" alt="Captura de pantalla 2025-07-17 161012" src="https://github.com/user-attachments/assets/2b33228a-b355-49ba-894d-e840750af31e" />
</div>








