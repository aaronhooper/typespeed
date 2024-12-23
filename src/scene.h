#pragma once

#include "word.h"

#include <stdint.h>

typedef enum Scene {
  SCENE_NULL = 0,
  SCENE_GAMEPLAY,
  SCENE_MAIN,
} Scene;

void scene_set(Scene scene);
void scene_update();
void scene_draw();
