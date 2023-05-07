#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define BALL_SIZE 10
#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 5

#define SPEED_MODIFIER .03f

typedef struct EntityStruct
{
    float x;
    float y;
    bool has_moved;
} Entity;

// https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
// TODO: this isn't perfectly working
bool intersects(Entity circle, Entity rect)
{
    int circle_distance_x = abs(circle.x - rect.x);
    int circle_distance_y = abs(circle.y - rect.y);

    if (circle_distance_x > (PLAYER_WIDTH / 2 + (BALL_SIZE / 2)))
    {
        return false;
    }
    if (circle_distance_y > (PLAYER_HEIGHT / 2 + (BALL_SIZE / 2)))
    {
        return false;
    }

    if (circle_distance_x <= (PLAYER_WIDTH / 2))
    {
        return true;
    }
    if (circle_distance_y <= (PLAYER_HEIGHT / 2))
    {
        return true;
    }

    int corner_distance_sq = (circle_distance_x - PLAYER_WIDTH / 2) ^ 2 + (circle_distance_y - PLAYER_HEIGHT / 2) ^ 2;

    return (corner_distance_sq <= ((BALL_SIZE / 2) ^ 2));
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib-pong");

    // Initalize game Data
    Entity ball = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    Entity player_one = {WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 2.0f, false};
    Entity player_two = {WINDOW_WIDTH - WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 2.0f, false};

    int player_one_score = 0;
    int player_two_score = 0;
    char *score_buf[50] = {};

    // Seed random
    srand(time(NULL));

    // have ball pick a random direction to start moving in
    Vector2 ball_speed = {rand() % 3, rand() % 3};

    // Main game loop
    while (!WindowShouldClose())
    {
        // == GAME LOGIC ==
        // check for player 1 input
        if (IsKeyDown(KEY_UP))
        {
            player_two.y -= .05f;
            player_two.has_moved = true;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player_two.y += .05f;
            player_two.has_moved = true;
        }
        else
        {
            player_two.has_moved = false;
        }

        // check for player 2 input
        if (IsKeyDown(KEY_W))
        {
            player_one.y -= .05f;
            player_one.has_moved = true;
        }
        else if (IsKeyDown(KEY_S))
        {
            player_one.y += .05f;
            player_one.has_moved = true;
        }
        else
        {
            player_one.has_moved = false;
        }

        // Give ball some speed
        ball.x += ball_speed.x * SPEED_MODIFIER;
        ball.y += ball_speed.y * SPEED_MODIFIER;

        // Check for OOB on left and right
        // TODO: extract into method
        if (ball.x < 0) 
        {
            player_two_score += 1;
            ball.x = WINDOW_WIDTH / 2.0f;
            ball.y = WINDOW_HEIGHT / 2.0f;
        }
        else if (ball.x > WINDOW_WIDTH) 
        {
            player_one_score += 1;
            ball.x = WINDOW_WIDTH / 2.0f;
            ball.y = WINDOW_HEIGHT / 2.0f;
        }

        // Handle ceiling collisions
        if ((ball.y >= (GetScreenHeight() - (BALL_SIZE / 2.0f))) || (ball.y <= (BALL_SIZE / 2.0f)))
        {
            ball_speed.y *= -1.0f;
        }

        // Handle paddle collisions - bounce back other way but keep vertical momentum
        if (intersects(ball, player_one) || intersects(ball, player_two))
        {
            ball_speed.x *= -1.0f;
        }

        // == DRAWING ==
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw entities
        DrawCircle(ball.x, ball.y, BALL_SIZE, GREEN);
        DrawRectangle(player_one.x, player_one.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);
        DrawRectangle(player_two.x, player_two.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);

        // Draw score
        sprintf(score_buf, "%d %d", player_one_score, player_two_score);
        DrawText(score_buf, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, 22, WHITE); // TODO: center this properly

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
