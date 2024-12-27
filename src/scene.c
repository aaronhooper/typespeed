#include "scene.h"
#include "memory/arena.h"
#include "scenes/gameplay.h"
#include "scenes/main.h"

#include <stdio.h>
#include <stdlib.h>

static Scene _scene_type;
static void *_scene_object;
static Arena _scene_arena = {0};
static bool _is_initialized = false;

Scene scene_get() { return _scene_type; }

void scene_set(Scene scene) {
  if (!_is_initialized) {
    arena_init(&_scene_arena, 1024 * 1024 * 1024);
    _is_initialized = true;
  }

  if (_scene_object != NULL) {
    arena_flush(&_scene_arena);
  }

  _scene_type = scene;

  switch (scene) {
  case SCENE_MAIN:
    _scene_object = scene_main_create(&_scene_arena);
    break;
  case SCENE_GAMEPLAY:
    _scene_object = scene_gameplay_create(&_scene_arena);
    break;
  case SCENE_NULL:
    arena_free(&_scene_arena);
    break;
  }
}

void scene_update() {
  switch (scene_get()) {
  case SCENE_MAIN:
    scene_main_update(_scene_object);
    break;
  case SCENE_GAMEPLAY:
    scene_gameplay_update(_scene_object);
    break;
  case SCENE_NULL:
  default:
    printf("the null scene, no update\n");
    break;
  }
}

void scene_draw() {
  switch (scene_get()) {
  case SCENE_MAIN:
    scene_main_draw(_scene_object);
    break;
  case SCENE_GAMEPLAY:
    scene_gameplay_draw(_scene_object);
    break;
  case SCENE_NULL:
  default:
    printf("the null scene, no draw\n");
    break;
  }
}
