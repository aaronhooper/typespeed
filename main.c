#include "raylib.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAMES_PER_SEC 60

static const char *WINDOW_TITLE = "typespeed";

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("This is the Raylib window", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
             12, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
