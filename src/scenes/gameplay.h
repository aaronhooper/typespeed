#pragma once

#include "components/word.h"
#include "components/player_input.h"

typedef struct SceneGameplayObject {
  PlayerInput player_input;
  Word *words;
  Slab words_slab;
  int score;
} SceneGameplayObject;

SceneGameplayObject *scene_gameplay_create(Arena *arena);
void scene_gameplay_update(SceneGameplayObject *scene);
void scene_gameplay_draw(SceneGameplayObject *scene);
