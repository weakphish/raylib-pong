#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

#define BALL_SIZE 10
#define PLAYER_HEIGHT 30
#define PLAYER_WIDTH 5

typedef struct BallStruct {
  int x;
  int y;
} Ball;

typedef struct PlayerStruct {
  int player_num;
  int x;
  int y;
} Player;

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib-pong");

  // Initalize game Data
  Ball playing_ball = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
  Player player_one = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4};

  // Main game loop
  while (!WindowShouldClose()) {
    // == GAME LOGIC ==
    // TODO

    // == DRAWING ==
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw ball's position
    DrawCircle(playing_ball.x, playing_ball.y, BALL_SIZE, GREEN);

    // Draw player one (left)
    DrawRectangle(player_one.x, player_one.y, PLAYER_WIDTH, PLAYER_HEIGHT, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
