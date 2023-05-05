#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define BALL_SIZE 10
#define PLAYER_HEIGHT 50
#define PLAYER_WIDTH 5

typedef struct EntityStruct {
  float x;
  float y;
  bool has_moved;
} Entity;

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib-pong");

  // Initalize game Data
  Entity ball = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
  Entity player_one = {WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 2.0f, false};
  Entity player_two = {WINDOW_WIDTH - WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 2.0f,
                       false};

  // Seed random
  srand(time(NULL));

  // have ball pick a random direction to start moving in
  int ball_dx = rand() % 3;
  int ball_dy = rand() % 3; 

  // Main game loop
  while (!WindowShouldClose()) {
    // Log positions if changed
    if (player_one.has_moved) {
      printf("Player position: (%f %f)\n", player_one.x, player_one.y);
    }
    if (player_two.has_moved) {
      printf("Player position: (%f %f)\n", player_one.x, player_one.y);
    }

    // == GAME LOGIC ==
    // check for player 1 input
    if (IsKeyDown(KEY_UP)) {
      player_two.y -= .05f;
      player_two.has_moved = true;
    } else if (IsKeyDown(KEY_DOWN)) {
      player_two.y += .05f;
      player_two.has_moved = true;
    } else {
      player_two.has_moved = false;
    }

    // check for player 2 input
    if (IsKeyDown(KEY_W)) {
      player_one.y -= .05f;
      player_one.has_moved = true;
    } else if (IsKeyDown(KEY_S)) {
      player_one.y += .05f;
      player_one.has_moved = true;
    } else {
      player_one.has_moved = false;
    }

    // Handle ball collison / movement
    ball.x += ball_dx * .03f;
    ball.y += ball_dy * .03f;

    if ((ball.x >= (GetScreenWidth() - (BALL_SIZE / 2.0f))) ||
        (ball.x <= (BALL_SIZE / 2.0f))) {
      ball_dx *= -1.0f;
    }
    if ((ball.y >= (GetScreenHeight() - (BALL_SIZE / 2.0f))) ||
        (ball.y <= (BALL_SIZE / 2.0f))) {
      ball_dy *= -1.0f;
    }

    // == DRAWING ==
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw ball's position
    DrawCircle(ball.x, ball.y, BALL_SIZE, GREEN);

    // Draw player one (left)
    DrawRectangle(player_one.x, player_one.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);

    // Draw player two (right)
    DrawRectangle(player_two.x, player_two.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
