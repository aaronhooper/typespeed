#include "gameplay.h"
#include "../components/player_input.h"
#include "../config.h"
#include "../util.h"
#include "memory/arena.h"
#include "memory/slab.h"
#include "word.h"

#include <stdlib.h>

SceneGameplayObject *scene_gameplay_create() {
  SceneGameplayObject *object = malloc(sizeof(SceneGameplayObject));
  Arena arena = {0};
  if (arena_init(&arena, 4096) == NULL) {
    return NULL;
  }

  Slab slab = {0};
  slab_init(&slab, &arena, sizeof(Word), 20);

  object->arena = arena;
  object->words_slab = slab;
  object->player_input = player_input_create(&arena);
  object->word_matched_wav = LoadWave("assets/word_matched.wav");
  object->word_matched = LoadSoundFromWave(object->word_matched_wav);
  object->dict = dict_load(WORDLIST_FILE);
  object->words = words_create(&arena, &slab, &object->dict, 20);
  object->score = 0;

  return object;
}

void scene_gameplay_free(SceneGameplayObject *object) {
  arena_free(&object->arena);
  UnloadSound(object->word_matched);
  UnloadWave(object->word_matched_wav);
  dict_free(object->dict);
  free(object);
  object = NULL;
}

void scene_gameplay_update(SceneGameplayObject *scene) {
  int keycode = GetKeyPressed();

  if (KEY_A <= keycode && keycode <= KEY_Z) {
    if (scene->player_input.size != scene->player_input.capacity) {
      player_input_push_key(&scene->player_input, (char)keycode + 32);
    }

    if (words_remove(&scene->words_slab, &scene->words,
                     scene->player_input.buffer)) {
      PlaySound(scene->word_matched);
      player_input_clear(&scene->player_input);
      ++scene->score;
    }
  }

  if (keycode == KEY_BACKSPACE) {
    player_input_pop_key(&scene->player_input);
  }

  words_update(scene->words);
}

void scene_gameplay_draw(SceneGameplayObject *scene) {
  words_draw(scene->words);
  player_input_draw(&scene->player_input);
  score_draw(scene->score);
}
