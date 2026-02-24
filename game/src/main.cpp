#include "raylib.h"
#include "raymath.h"

constexpr float paddle_width = 20.0f;
constexpr float paddle_height = 80.0f;

void DrawPaddle(Vector2 position)
{
    Rectangle paddle;
    paddle.x = position.x - paddle_width * 0.5f;
    paddle.y = position.y - paddle_height * 0.5f;
    paddle.width = paddle_width;
    paddle.height = paddle_height;
    DrawRectangleRec(paddle, WHITE);
}

int main()
{
    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);
    
    float paddle_margin = GetScreenWidth() * 0.025f;
    Vector2 paddle1_position = { paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 paddle2_position = { GetScreenWidth() - paddle_margin, GetScreenHeight() * 0.5f };

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        DrawPaddle(paddle1_position);
        DrawPaddle(paddle2_position);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
