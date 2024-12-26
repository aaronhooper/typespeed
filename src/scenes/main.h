#pragma once

#include "components/title.h"
#include "components/play_button.h"

typedef struct SceneMainObject {
  Title *title;
  PlayButton *play_button;
} SceneMainObject;

SceneMainObject *scene_main_create(Arena *arena);
void scene_main_update(SceneMainObject *scene);
void scene_main_draw(SceneMainObject *scene);
