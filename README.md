# 🏓 Ping-Pong Game

A simple **Ping-Pong game** built in **C++** using the **Raylib** library.  
Enjoy classic Pong gameplay with smooth controls and a CPU opponent! 🎮  

---
## ⚡ Quick Start  

1. Complete the **Setup Guide** .
2. Clone this repository:  
   ```bash
   git clone https://github.com/amancod/ping-pong.git
   ```
3. Open the ping-pong.sln file in Visual Studio.
4. Press CTRL + F5 to build and run the project.

🎉 Congratulations! Your Ping-Pong game is up and running.
---

## 🚀 Features
- Classic Pong gameplay 🎾  
- CPU opponent with basic AI 🤖  
- Player-controlled paddle with keyboard input ⌨️  
- Collision detection & ball bouncing 🟡  
- Score tracking for both sides 🏆  
- Colored background and styled paddles 🎨  

---

## 🛠️ Tech Stack
- **Language:** C++  
- **Library:** Raylib  
- **IDE (Optional):** Visual Studio Community Edition 2022  

---

## 🛠️ Prerequisites
Before building the game, make sure you have the following installed:

- **Microsoft Visual Studio Community Edition 2022** (with *Desktop development with C++* workload)  
- **vcpkg** (C++ package manager)  
- **git**  
- **Raylib** (installed via vcpkg)  

---

## ⚡ Setup Guide

### 1️⃣ Install Visual Studio
- Download **Visual Studio Community 2022**.  
- Run the installer and select **Desktop development with C++** workload.  
- After installation, create a **C++ Console App** and run a "Hello World" program to confirm setup.  

---

### 2️⃣ Install vcpkg
```bash
# Clone vcpkg
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# Bootstrap vcpkg
./bootstrap-vcpkg.bat

# Integrate with Visual Studio
./vcpkg integrate install
```
### 3️⃣ Install Raylib with vcpkg
```bash
./vcpkg install raylib:x64-windows
```

### 4️⃣ Import Raylib into Your Project
```bash
#include "raylib.h"
```

### 5️⃣ Test with Bouncing Ball Example
```bash
#include "raylib.h"

int main() {
    InitWindow(800, 450, "Bouncing Ball Example");
    Vector2 ball = {400, 225};
    Vector2 speed = {5, 4};
    int radius = 20;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        ball.x += speed.x;
        ball.y += speed.y;

        if (ball.x < radius || ball.x > GetScreenWidth()-radius) speed.x *= -1;
        if (ball.y < radius || ball.y > GetScreenHeight()-radius) speed.y *= -1;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(ball, radius, MAROON);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

### 🎮 Controls

- Arrow Up → Move paddle up
- Arrow Down → Move paddle down
- ESC → Quit game

## 📸 Preview

<img width="1279" height="832" alt="image" src="https://github.com/user-attachments/assets/0e8f38db-ea1e-4cf4-ab08-994fcd449860" />


---


