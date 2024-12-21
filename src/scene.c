#include "scene.h"
#include "config.h"
#include "dict.h"
#include "player_input.h"
#include "raylib.h"
#include "util.h"
#include "word.h"

#include <stdio.h>
#include <stdlib.h>

static Scene _scene_type;
static void *_scene_object;

Scene scene_get() { return _scene_type; }

SceneGameplayObject *scene_gameplay_create() {
  char *player_input = malloc(MAX_WORD_LENGTH * sizeof(char));
  SceneGameplayObject *object = malloc(sizeof(SceneGameplayObject));

  object->player_input = player_input;
  object->word_matched_wav = LoadWave("assets/word_matched.wav");
  object->word_matched = LoadSoundFromWave(object->word_matched_wav);
  object->dict = dict_load(WORDLIST_FILE);
  object->words = words_create(&object->dict, 20);
  object->score = 0;

  return object;
}

void scene_gameplay_free(SceneGameplayObject *object) {
  free(object->player_input);
  words_free(object->words);
  UnloadSound(object->word_matched);
  UnloadWave(object->word_matched_wav);
  dict_free(&object->dict);
  free(object);
  object = NULL;
}

void scene_free(Scene scene) {
  switch (scene) {
  case SCENE_MAIN:
    break;
  case SCENE_GAMEPLAY:
    scene_gameplay_free(_scene_object);
  case SCENE_NULL:
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
    break;
  case SCENE_GAMEPLAY:
    _scene_object = scene_gameplay_create();
    break;
  case SCENE_NULL:
    break;
  }
}

void scene_gameplay_update(SceneGameplayObject *scene) {
  int keycode = GetKeyPressed();

  if (KEY_A <= keycode && keycode <= KEY_Z) {
    player_input_push_key(scene->player_input, (char)keycode + 32);

    if (words_remove(&scene->words, scene->player_input)) {
      PlaySound(scene->word_matched);
      player_input_clear(scene->player_input);
      ++scene->score;
    }
  }

  if (keycode == KEY_BACKSPACE) {
    player_input_pop_key(scene->player_input);
  }

  words_update(scene->words);
}

void scene_gameplay_draw(SceneGameplayObject *scene) {
  words_draw(scene->words);
  player_input_draw(scene->player_input);
  score_draw(scene->score);
}

void scene_update() {
  switch (scene_get()) {
  case SCENE_MAIN:
    printf("the main scene update\n");
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
    printf("the main scene draw\n");
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
