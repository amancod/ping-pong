#include <raylib.h>
#include <iostream>

// 🎨 Colors (constants for theming)
const Color Green = { 38, 185, 154, 255 };
const Color Dark_Green = { 20, 160, 133, 255 };
const Color Light_Green = { 129, 204, 184, 255 };
const Color Yellow = { 243, 213, 91, 255 };

// 🏆 Scores
int cpuScore = 0;
int playerScore = 0;

// 🎾 Ball Class
class Ball {
public:
    float x, y;
    int radius;
    int speedX, speedY;

    Ball(int startX, int startY, int r, int sx, int sy) {
        x = startX; y = startY;
        radius = r; speedX = sx; speedY = sy;
    }

    void Draw() const {
        DrawCircle((int)x, (int)y, radius, Yellow);
    }

    void Update() {
        x += speedX;
        y += speedY;

        // Bounce off top/bottom
        if (y <= radius || y >= GetScreenHeight() - radius) {
            speedY *= -1;
        }

        // Left boundary → player scores
        if (x <= radius) {
            playerScore++;
            Reset();
        }

        // Right boundary → CPU scores
        if (x >= GetScreenWidth() - radius) {
            cpuScore++;
            Reset();
        }

        // Clamp to screen if resized smaller
        if (x - radius < 0) x = radius;
        if (x + radius > GetScreenWidth()) x = GetScreenWidth() - radius;
        if (y - radius < 0) y = radius;
        if (y + radius > GetScreenHeight()) y = GetScreenHeight() - radius;
    }

    void Reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int dirX[2] = { -1, 1 };
        int dirY[2] = { -1, 1 };
        speedX = (abs(speedX) == 0 ? 7 : abs(speedX)) * dirX[GetRandomValue(0, 1)];
        speedY = (abs(speedY) == 0 ? 7 : abs(speedY)) * dirY[GetRandomValue(0, 1)];
    }
};

// 🏓 Base Paddle Class
class Paddle {
protected:
    void ClampToScreen() {
        if (y < 0) y = 0;
        if (y > GetScreenHeight() - height) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    Paddle(float px, float py, float w, float h, int s) {
        x = px; y = py; width = w; height = h; speed = s;
    }

    virtual void Update() = 0;  // pure virtual (forces subclasses to define)

    void Draw() const {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8f, 0, WHITE);
    }
};

// 👤 Player Paddle
class PlayerPaddle : public Paddle {
public:
    PlayerPaddle(float px, float py, float w, float h, int s)
        : Paddle(px, py, w, h, s) {
    }

    void Update() override {
        if (IsKeyDown(KEY_UP))   y -= speed;
        if (IsKeyDown(KEY_DOWN)) y += speed;
        ClampToScreen();
    }
};

// 🤖 CPU Paddle
class CpuPaddle : public Paddle {
private:
    float targetY;  // Ball Y to track
public:
    CpuPaddle(float px, float py, float w, float h, int s)
        : Paddle(px, py, w, h, s), targetY(0) {
    }

    void SetTargetY(float ballY) { targetY = ballY; }

    void Update() override {
        if (y + height / 2 < targetY) y += speed;
        if (y + height / 2 > targetY) y -= speed;
        ClampToScreen();
    }
};


// 🎮 Main Game
int main() {
    std::cout << "Starting Ping Pong Game..." << std::endl;

    const int INITIAL_WIDTH = 1280;
    const int INITIAL_HEIGHT = 800;

    // ✅ Enable resizable window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Ping Pong Game (Resizable)");
    SetTargetFPS(60);

    // Create objects
    Ball ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 20, 7, 7);
    PlayerPaddle player(GetScreenWidth() - 35, GetScreenHeight() / 2 - 60, 25, 120, 10);
    CpuPaddle cpu(10, GetScreenHeight() / 2 - 60, 25, 120, 10);

    while (!WindowShouldClose()) {
        // Updates
        ball.Update();

        player.x = GetScreenWidth() - player.width - 10;
        player.Update();

        cpu.SetTargetY(ball.y);
        cpu.Update();

        // Ball collisions with paddles
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
            Rectangle{ player.x, player.y, player.width, player.height })) {
            ball.speedX *= -1;
            ball.x = player.x - ball.radius; // prevent sticking
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
            Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
            ball.speedX *= -1;
            ball.x = cpu.x + cpu.width + ball.radius;
        }

        // 🎨 Drawing
        BeginDrawing();
        ClearBackground(Dark_Green);

        int sw = GetScreenWidth();
        int sh = GetScreenHeight();

        // Middle field
        DrawRectangle(sw / 2, 0, sw / 2, sh, Green);
        DrawCircle(sw / 2, sh / 2, 150, Light_Green);
        DrawLine(sw / 2, 0, sw / 2, sh, WHITE);

        // Objects
        ball.Draw();
        player.Draw();
        cpu.Draw();

        // Scores
        DrawText(TextFormat("%i", cpuScore), sw / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), sw * 3 / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
