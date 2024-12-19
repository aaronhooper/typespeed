#include "config.h"
#include "raylib.h"
#include "word.h"

#include <stdio.h>
#include <string.h>

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
  char typed_word[MAX_WORD_LENGTH] = "";

  while (!WindowShouldClose()) {
    // update typed word
    for (int keycode = KEY_A; keycode <= KEY_Z; ++keycode) {
      if (IsKeyPressed(keycode)) {
        char key_lowercase = (char)keycode + 32;
        int len = strlen(typed_word);
        typed_word[len] = key_lowercase;
        typed_word[len + 1] = '\0';

        if (words_remove(words, typed_word)) {
          typed_word[0] = '\0';
        }
      }
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
      int len = strlen(typed_word);

      if (len != 0) {
        typed_word[len - 1] = '\0';
      }
    }

    words_update(words);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    words_draw(words);
    DrawText(typed_word, 0, SCREEN_HEIGHT - 24, 24, GRAY); // draw typed word

#ifdef _DEBUG
    fps_draw();
#endif

    EndDrawing();
  }

  CloseWindow();

  words_free(words);
  dict_free(dict);

  return 0;
}
