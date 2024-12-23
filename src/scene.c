#include "scene.h"
#include "scenes/gameplay.h"
#include "scenes/main.h"

#include <stdio.h>
#include <stdlib.h>

static Scene _scene_type;
static void *_scene_object;

Scene scene_get() { return _scene_type; }

void scene_free(Scene scene) {
  switch (scene) {
  case SCENE_MAIN:
    scene_main_free(_scene_object);
    break;
  case SCENE_GAMEPLAY:
    scene_gameplay_free(_scene_object);
    break;
  case SCENE_NULL:
  default:
    break;
  }
}

void scene_set(Scene scene) {
  if (_scene_object != NULL) {
    scene_free(scene_get());
  }

  _scene_type = scene;

  switch (scene) {
  case SCENE_MAIN:
    _scene_object = scene_main_create();
    break;
  case SCENE_GAMEPLAY:
    _scene_object = scene_gameplay_create();
    break;
  case SCENE_NULL:
  default:
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
