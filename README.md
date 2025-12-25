# 🚦 Crossing Road Game (C++ Console – Windows)

A **Crossing Road / Frogger-style console game** written in **C++** using the **Windows Console API (WinAPI)**.  
The game features animated traffic, animals, sound effects, save/load functionality, leaderboard, and a full interactive menu system.

> ⚠️ **Windows only** – this project depends on `Windows.h`, `conio.h`, WinAPI console functions, and `PlaySound`.

---

## 🎮 Gameplay Overview

- Control a player trying to cross multiple dangerous lanes
- Avoid cars, trucks, vans, birds, and pigs
- Reach the top to score points and increase the level
- Game speed increases as the level goes up
- Collision results in a game-over animation

---

## ✨ Features

- ASCII & Unicode-based console graphics
- Real-time movement and animation
- Multiple object types (Car, Truck, Van, Bird, Pig)
- Sound effects and background music (`.wav`)
- Pause / Resume gameplay
- Save & Load game state
- Leaderboard (Top scores)
- Settings menu (toggle music)
- Animated main menu and UI

---

## ⌨️ Controls

| Key | Action |
|----|------|
| **W / ↑** | Move Up |
| **S / ↓** | Move Down |
| **A / ←** | Move Left |
| **D / →** | Move Right |
| **P** | Pause / Resume |
| **L** | Save Game |
| **M** | Toggle Game Music |
| **Q / ESC** | Quit |
| **ENTER** | Confirm selection |

---


## 💾 Save & Load System

- Saved games are stored as `.txt` files
- `saveGameList.txt` keeps track of saved game names
- `saveScoreList.txt` stores leaderboard data
- Load saved games from **LOAD GAME** in the main menu

---

## 🏆 Leaderboard

- Automatically stores player scores
- Sorted in descending order
- Displays top 10 scores
- Shown both in-game and in the main menu

---

## 🔊 Audio

- Background music for menu and gameplay
- Collision and animal sound effects
- Toggle music ON/OFF from **Settings**

> Required library: `winmm.lib`

---

## ▶️ Build & Run

### Requirements
- Windows OS
- Visual Studio (recommended) **or** MinGW
- C++17 or later

### Build with Visual Studio
1. Open `CrossingRoad.sln`
2. Build the solution (`Ctrl + Shift + B`)
3. Run the project

### Build with MinGW (optional)
```bash
g++ main.cpp -o CrossingRoad -lwinmm
```
```bash
CrossingRoad.exe
```

---

## 🧠 OOP Design

- `CObject` (abstract base class)
  - `CCar`, `CTruck`, `CVan`, `CBird`, `CPig`
- `CLane` – manages moving objects
- `CPlayer` – player state and score
- `CGame` – core game loop and logic

Demonstrates:
- Inheritance & polymorphism
- Dynamic memory management
- File I/O
- Real-time input handling

---

## 📌 Notes

- Console size is fixed for best visuals
- Uses Unicode box-drawing characters
- Designed as a **DSA & OOP learning project**
- Windows-only by design

---

## 📜 License

This project is for **educational purposes**.  
You are free to use, modify, and improve it.
