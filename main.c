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

void typed_word_clear(char *typed_word) {
  memset(typed_word, 0, strlen(typed_word));
  typed_word[0] = '\0';
}

size_t words_len(Word *words) {
  Word *curr = words;
  size_t len = 0;

  while (curr != NULL) {
    len++;
    curr = curr->next;
  }

  return len;
}

const char *to_bool_string(int b) {
  static const char *true_s = "true";
  static const char *false_s = "false";
  return b == 0 ? true_s : false_s;
}

int main(void) {
  InitAudioDevice();
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);

  Wave word_matched_wav = LoadWave("word_matched.wav");
  Sound word_matched = LoadSoundFromWave(word_matched_wav);
  Dict *dict = dict_load(WORDLIST_FILE, 10000);
  size_t words_size = 20;
  Word *words = words_create(dict, words_size);
  char typed_word[MAX_WORD_LENGTH] = "";

  while (!WindowShouldClose()) {
    int keycode = GetKeyPressed();

    if (KEY_A <= keycode && keycode <= KEY_Z) {
      typed_word_push(typed_word, (char)keycode + 32);

      if (words_remove(&words, typed_word)) {
        PlaySound(word_matched);
        typed_word_clear(typed_word);
      }
    }

    if (keycode == KEY_BACKSPACE) {
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
  CloseAudioDevice();

  words_free(words);
  dict_free(dict);

  return 0;
}
