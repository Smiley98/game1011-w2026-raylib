#include "raylib.h"
#include "raymath.h"

constexpr float paddle_width = 20.0f;
constexpr float paddle_height = 100.0f;

void DrawRec(Vector2 position, float width, float height)
{
    Rectangle rec;
    rec.x = position.x - width * 0.5f;
    rec.y = position.y - height * 0.5f;
    rec.width = width;
    rec.height = height;
    DrawRectangleRec(rec, WHITE);
}

int main()
{
    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);
    
    float paddle_margin = GetScreenWidth() * 0.025f;
    float paddle_speed = 500.0f;
    Vector2 paddle1_position = { paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 paddle2_position = { GetScreenWidth() - paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 ball_position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_W))
            paddle1_position.y -= paddle_speed * dt;

        if (IsKeyDown(KEY_S))
            paddle1_position.y += paddle_speed * dt;

        if (IsKeyDown(KEY_UP))
            paddle2_position.y -= paddle_speed * dt;

        if (IsKeyDown(KEY_DOWN))
            paddle2_position.y += paddle_speed * dt;

        paddle1_position.y = Clamp(paddle1_position.y, paddle_height * 0.5f, GetScreenHeight() - paddle_height * 0.5f);
        paddle2_position.y = Clamp(paddle2_position.y, paddle_height * 0.5f, GetScreenHeight() - paddle_height * 0.5f);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRec(paddle1_position, paddle_width, paddle_height);
        DrawRec(paddle2_position, paddle_width, paddle_height);
        DrawRec(ball_position, 20.0f, 20.0f);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
