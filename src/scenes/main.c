#include "main.h"
#include "memory/arena.h"
#include "title.h"

#include <stdlib.h>

SceneMainObject *scene_main_create() {
  SceneMainObject *object = malloc(sizeof(SceneMainObject));
  Arena arena = {0};

  if (arena_init(&arena, 1024) == NULL) {
    return NULL;
  }

  object->arena = arena;
  object->title = title_create(&arena);
  object->play_button = play_button_create();

  return object;
}

void scene_main_free(SceneMainObject *object) {
  play_button_free(object->play_button);
  arena_free(&object->arena);
  free(object);
}

void scene_main_update(SceneMainObject *scene) {
  title_update(scene->title);
  play_button_update(scene->play_button);
}

void scene_main_draw(SceneMainObject *scene) {
  title_draw(scene->title);
  play_button_draw(scene->play_button);
}
