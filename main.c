#include "config.h"
#include "raylib.h"
#include "word.h"

#include <stdio.h>

void fps_draw() {
  char buffer[15];
  snprintf(buffer, sizeof(buffer), "FPS: %d", GetFPS());
  DrawText(buffer, 0, 0, 16, GRAY);
}

int main(void) {
  Dict *dict = dict_load(WORDLIST_FILE, 10000);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);

  size_t words_size = 20;
  Word *words = words_create(dict, words_size);

  while (!WindowShouldClose()) {
    words_update(words);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    words_draw(words);
    fps_draw();
    EndDrawing();
  }

  CloseWindow();
  words_free(words);
  dict_free(dict);

  return 0;
}
