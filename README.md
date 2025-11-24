# 🐍 Snake Game — GUI Edition

A polished graphical Snake Game built in *C* using *Raylib*, featuring smooth movement animation, food consumption mechanics, score tracking, restart system, and a responsive grid-based user interface.

## Features

### Gameplay

* Classic Snake gameplay on a **15×15 grid**.
* Player-controlled movement using arrow keys.
* Smooth frame-based movement at *10 FPS*.
* Random food spawning with collision-safe placement.
* Snake grows after every food item eaten.
* Game ends on:

  * Wall collision
  * Self-collision
* Press **ENTER** to restart immediately.

### Visuals & UI

* Built entirely with *Raylib*.
* Clean and simple grid visuals.
* Snake body rendered in green, food in red.
* Real-time score shown at the top-left.
* Dedicated **Game Over** overlay screen.
* Uses a state machine for clean screen transitions.

### Sound Effects

* “eat.mp3” plays when food is eaten.
* “wall.mp3” plays on collisions.
* Audio managed through Raylib’s audio device module.

---

## Scoring System

* Score increases by **+1 for each food eaten**.
* No score penalties for steps taken.
* Score resets after restart.
* Score displayed continuously on-screen during gameplay.

---

## Technologies Used

* *Language:* C
* *Graphics/Audio Library:* Raylib
* *Compiler:* GCC (MSYS2 MinGW-w64)
* *Editor:* Visual Studio Code / Dev-C++
* *Build System:* Manual GCC linking

---

## How to Build & Run

### 1. Install Raylib (MSYS2)

```bash
pacman -S mingw-w64-x86_64-raylib
```

### 2. Compile

```bash
gcc snake.c -o snake -lraylib -lopengl32 -lgdi32 -lwinmm
```

### 3. Run

```bash
./snake.exe
```

⚠ **Make sure the `Sounds/` folder is in the same directory as the executable**, otherwise audio will not load.

---

## Game Flow

```
Start
 ↓
Initialize Game (window, audio, snake, food)
 ↓
GAME_PLAYING State
 ↓
Read Input → Move Snake → Check Food → Check Collision
 ↓
If Collision → GAME_OVER State
 ↓
Press ENTER to Restart
 ↓
Reset Snake & Score
 ↓
Return to GAME_PLAYING
```

---

## Future Enhancements

* Add difficulty modes (speed increases).
* Add textures for snake and food.
* Add menu screens (main menu, settings).
* Add high-score saving system.
* Add pause functionality.
* Add particle effects or animations.

---

## Limitations

* No AI or CPU behavior.
* No saving system for scores.
* Grid size is fixed at 15×15.
* Requires Raylib DLLs on other machines.
* No keyboard remapping options.

---

## Author

**Moazamuddin Shaikh**
*FAST-NUCES Karachi*
*Programming Fundamentals Project — Fall 2025*


