#pragma once

#include "../components/word.h"
#include "player_input.h"

typedef struct SceneGameplayObject {
  Arena arena;
  PlayerInput player_input;
  Word *words;
  Wave word_matched_wav;
  Sound word_matched;
  Dict dict;
  int score;
} SceneGameplayObject;

SceneGameplayObject *scene_gameplay_create();
void scene_gameplay_free(SceneGameplayObject *object);
void scene_gameplay_update(SceneGameplayObject *scene);
void scene_gameplay_draw(SceneGameplayObject *scene);
