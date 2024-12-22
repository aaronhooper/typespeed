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

typedef struct Title {
  const char *text;
  int font_size;
  int x;
  int y;
} Title;

typedef struct PlayButton {
  const char *text;
  int font_size;
  Color color;
  int x;
  int y;
} PlayButton;

typedef struct SceneMainObject {
  Title *title;
  PlayButton *play_button;
} SceneMainObject;

void scene_set(Scene scene);
void scene_update();
void scene_draw();
