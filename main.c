#include "config.h"
#include "dict.h"
#include "raylib.h"
#include "word.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_fps_counter() {
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
    draw_fps_counter();
    EndDrawing();
  }

  CloseWindow();
  words_free(words);
  dict_free(dict);

  return 0;
}
