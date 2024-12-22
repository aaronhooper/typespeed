#pragma once

#include "word.h"
#include <stdint.h>

typedef enum Scene {
  SCENE_NULL = 0,
  SCENE_GAMEPLAY,
  SCENE_MAIN,
} Scene;

typedef struct SceneGameplayObject {
  char *player_input;
  Word *words;
  Wave word_matched_wav;
  Sound word_matched;
  Dict dict;
  int score;
} SceneGameplayObject;

typedef struct SceneMainObject {
  const char *title_text;
  int title_font_size;
  int title_x;
  int title_y;
  const char *play_button_text;
  int play_button_font_size;
  unsigned char play_button_opacity;
  int play_button_x;
  int play_button_y;
} SceneMainObject;

void scene_set(Scene scene);
void scene_update();
void scene_draw();
