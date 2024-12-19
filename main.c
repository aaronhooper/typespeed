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

void typed_word_push(char *typed_word, char key) {
  int len = strlen(typed_word);
  typed_word[len] = key;
  typed_word[len + 1] = '\0';
}

void typed_word_pop(char *typed_word) {
  int len = strlen(typed_word);

  if (len != 0) {
    typed_word[len - 1] = '\0';
  }
}

void typed_word_clear(char *typed_word) { typed_word[0] = '\0'; }

int main(void) {
  Dict *dict = dict_load(WORDLIST_FILE, 10000);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);

  size_t words_size = 20;
  Word *words = words_create(dict, words_size);
  char typed_word[MAX_WORD_LENGTH] = "";

  while (!WindowShouldClose()) {
    for (int keycode = KEY_A; keycode <= KEY_Z; ++keycode) {
      if (IsKeyPressed(keycode)) {
        typed_word_push(typed_word, (char)keycode + 32);

        if (words_remove(words, typed_word)) {
          typed_word_clear(typed_word);
          break;
        }
      }
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
      typed_word_pop(typed_word);
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
