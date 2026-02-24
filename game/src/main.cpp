#include "raylib.h"
#include "raymath.h"

constexpr float paddle_width = 20.0f;
constexpr float paddle_height = 100.0f;
constexpr float ball_size = 20.0f;

void DrawRec(Vector2 position, float width, float height);

Vector2 RandomBallDirection(Vector2 direction/*Either [1, 0], or [-1, 0]*/)
{
    float angle = GetRandomValue(-45, 45);
    direction = Vector2Rotate(direction, angle * DEG2RAD);
    return direction;
}

int main()
{
    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);
    SetRandomSeed(GetTime());
    
    float paddle_margin = GetScreenWidth() * 0.025f;
    float paddle_speed = 500.0f;
    float ball_speed = 300.0f;
    Vector2 paddle1_position = { paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 paddle2_position = { GetScreenWidth() - paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 ball_position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    Vector2 ball_direction = RandomBallDirection(Vector2UnitX);

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

        ball_position += ball_direction * ball_speed * dt;
        if (ball_position.y - ball_size * 0.5f <= 0.0f || ball_position.y + ball_size * 0.5f >= GetScreenHeight())
            ball_direction.y *= -1.0f;
        if (ball_position.x - ball_size * 0.5f <= 0.0f || ball_position.x + ball_size * 0.5f >= GetScreenWidth())
            ball_direction.x *= -1.0f;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRec(paddle1_position, paddle_width, paddle_height);
        DrawRec(paddle2_position, paddle_width, paddle_height);
        DrawRec(ball_position, ball_size, ball_size);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawRec(Vector2 position, float width, float height)
{
    Rectangle rec;
    rec.x = position.x - width * 0.5f;
    rec.y = position.y - height * 0.5f;
    rec.width = width;
    rec.height = height;
    DrawRectangleRec(rec, WHITE);
}
