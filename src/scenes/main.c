#include "main.h"
#include "memory/arena.h"
#include "title.h"

SceneMainObject *scene_main_create(Arena *arena) {
  SceneMainObject *object = arena_alloc(arena, sizeof(SceneMainObject));
  object->title = title_create(arena);
  object->play_button = play_button_create(arena);

  return object;
}

void scene_main_update(SceneMainObject *scene) {
  title_update(scene->title);
  play_button_update(scene->play_button);
}

void scene_main_draw(SceneMainObject *scene) {
  title_draw(scene->title);
  play_button_draw(scene->play_button);
}
