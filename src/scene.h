#pragma once

#include "word.h"

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
  const char *title;
  int title_font_size;
} SceneMainObject;

void scene_set(Scene scene);
void scene_update();
void scene_draw();
