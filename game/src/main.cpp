#include "raylib.h"
#include "raymath.h"

constexpr float paddle_width = 20.0f;
constexpr float paddle_height = 100.0f;
constexpr float ball_size = 20.0f;

Rectangle GetRec(Vector2 position/*centre*/, float width, float height)
{
    Rectangle rec;
    rec.x = position.x - width * 0.5f;
    rec.y = position.y - height * 0.5f;
    rec.width = width;
    rec.height = height;
    return rec;
}

Vector2 RandomBallDirection(Vector2 direction/*Either [1, 0], or [-1, 0]*/)
{
    float angle = GetRandomValue(-45, 45);
    direction = Vector2Rotate(direction, angle * DEG2RAD);
    return direction;
}

int main()
{
    InitWindow(1280, 720, "Game");
    InitAudioDevice();
    SetRandomSeed(GetTime());
    SetTargetFPS(60);

    Sound sound_hit = LoadSound("pong_hit.mp3");

    float paddle_margin = GetScreenWidth() * 0.025f;
    float paddle_speed = 500.0f;
    float ball_speed = 300.0f;
    Vector2 paddle1_position = { paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 paddle2_position = { GetScreenWidth() - paddle_margin, GetScreenHeight() * 0.5f };
    Vector2 ball_position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    Vector2 ball_direction = RandomBallDirection(Vector2UnitX);
    int player1_score = 0;
    int player2_score = 0;

    float ball_reset_current = 0.0f;
    const float ball_reset_total = 2.0f;

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

        ball_reset_current += dt;
        if (ball_reset_current > ball_reset_total)
            ball_position += ball_direction * ball_speed * dt;

        // May need to offset position of ball when detecting collision to avoid unstable timestamp jittering bugs
        // + ball_direction * ball_speed * dt
        Rectangle ball_rec = GetRec(ball_position, ball_size, ball_size);
        Rectangle paddle1_rec = GetRec(paddle1_position, paddle_width, paddle_height);
        Rectangle paddle2_rec = GetRec(paddle2_position, paddle_width, paddle_height);

        if (CheckCollisionRecs(ball_rec, paddle1_rec) || CheckCollisionRecs(ball_rec, paddle2_rec))
        {
            ball_direction.x *= -1.0f;
            PlaySound(sound_hit);
        }

        if (ball_position.y - ball_size * 0.5f <= 0.0f || ball_position.y + ball_size * 0.5f >= GetScreenHeight())
        {
            ball_direction.y *= -1.0f;
            PlaySound(sound_hit);
        }

        // Player 1 goal (left player score on right net)
        if (ball_position.x + ball_size * 0.5f >= GetScreenWidth())
        {
            ball_position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
            ball_direction = RandomBallDirection(Vector2UnitX * -1.0f);
            player1_score++;
            ball_reset_current = 0.0f;
        }

        // Player 2 goal (right player score on left net)
        if (ball_position.x - ball_size * 0.5f <= 0.0f)
        {
            ball_position = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
            ball_direction = RandomBallDirection(Vector2UnitX);
            player2_score++;
            ball_reset_current = 0.0f;
        }

        // TODO -- Add a win screen when the score limit is reached, give the players an option to rematch!
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(paddle1_rec, WHITE);
            DrawRectangleRec(paddle2_rec, WHITE);
            DrawRectangleRec(ball_rec, WHITE);
            DrawText(TextFormat("%i", player1_score), GetScreenWidth() * 0.25f, GetScreenHeight() * 0.1f, 32, WHITE);
            DrawText(TextFormat("%i", player2_score), GetScreenWidth() * 0.75f, GetScreenHeight() * 0.1f, 32, WHITE);
            // TODO -- Add text in the top-centre counting down the time until the ball moves!
        EndDrawing();
    }

    UnloadSound(sound_hit);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
