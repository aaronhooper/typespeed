#include "config.h"
#include "player_input.h"
#include "raylib.h"
#include "util.h"
#include "word.h"

#include <stdio.h>
#include <string.h>

int main(void) {
  InitAudioDevice();
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);

  Wave word_matched_wav = LoadWave("assets/word_matched.wav");
  Sound word_matched = LoadSoundFromWave(word_matched_wav);
  Dict dict = dict_load(WORDLIST_FILE);
  size_t words_size = 20;
  Word *words = words_create(&dict, words_size);
  char player_input[MAX_WORD_LENGTH] = "";
  int score = 0;

  while (!WindowShouldClose()) {
    int keycode = GetKeyPressed();

    if (KEY_A <= keycode && keycode <= KEY_Z) {
      player_input_push_key(player_input, (char)keycode + 32);

      if (words_remove(&words, player_input)) {
        PlaySound(word_matched);
        player_input_clear(player_input);
        ++score;
      }
    }

    if (keycode == KEY_BACKSPACE) {
      player_input_pop_key(player_input);
    }

    words_update(words);

    BeginDrawing();
    ClearBackground(LIQUORICE);
    words_draw(words);
    player_input_draw(player_input);
    score_draw(score);

#ifdef _DEBUG
    fps_draw();
#endif

    EndDrawing();
  }

  CloseWindow();
  CloseAudioDevice();

  words_free(words);
  dict_free(&dict);

  return 0;
}
