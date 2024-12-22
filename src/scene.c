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

PlayButton *play_button_create() {
  PlayButton *button = malloc(sizeof(PlayButton));

  int screen_center_x = SCREEN_WIDTH / 2;
  int screen_center_y = SCREEN_HEIGHT / 2;

  // set the text top left position to title font size
  int play_button_x = screen_center_x;
  int play_button_y = screen_center_y;

  button->text = "play";
  button->font_size = 36;

  // subtract text midpoint from x and y pos of text to
  // get the centered position
  int play_button_width = MeasureText(button->text, button->font_size);
  int play_button_height = button->font_size;
  play_button_x = play_button_x - (play_button_width / 2);
  play_button_y = play_button_y - (play_button_height / 2);

  // move button down
  play_button_y += 100;

  button->x = play_button_x;
  button->y = play_button_y;
  button->color.r = 0xff;
  button->color.g = 0xff;
  button->color.b = 0xff;
  button->color.a = 0xff - 0xff / 4;

  return button;
}

SceneMainObject *scene_main_create() {
  SceneMainObject *object = malloc(sizeof(SceneMainObject));
  object->title_text = WINDOW_TITLE;
  object->title_font_size = 48;

  // TITLE
  // get center coords of screen
  int screen_center_x = SCREEN_WIDTH / 2;
  int screen_center_y = SCREEN_HEIGHT / 2;

  // set the text top left corner to the screen center
  int title_x = screen_center_x;
  int title_y = screen_center_y;

  // subtract text midpoint from x and y pos of text to
  // get the centered position
  int title_width = MeasureText(object->title_text, object->title_font_size);
  int title_height = object->title_font_size;
  title_x = title_x - (title_width / 2);
  title_y = title_y - (title_height / 2);

  object->title_x = title_x;
  object->title_y = title_y;

  object->play_button = play_button_create();

  return object;
}

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

void play_button_free(PlayButton *button) { free(button); }

void scene_main_free(SceneMainObject *object) {
  play_button_free(object->play_button);
  free(object);
}

void scene_gameplay_free(SceneGameplayObject *object) {
  free(object->player_input);
  words_free(object->words);
  UnloadSound(object->word_matched);
  UnloadWave(object->word_matched_wav);
  dict_free(object->dict);
  free(object);
  object = NULL;
}

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

void play_button_update(PlayButton *button) {
  int xstart = button->x;
  int xend = MeasureText(button->text, button->font_size) + SCREEN_WIDTH;
  int ystart = button->y;
  int yend = button->font_size + SCREEN_HEIGHT;
  int mousex = GetMouseX();
  int mousey = GetMouseY();

  bool is_within_x = xstart < mousex && mousex < xend;
  bool is_within_y = ystart < mousey && mousey < yend;

  if (is_within_x && is_within_y) {
    button->color.a = 0xff;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      scene_set(SCENE_GAMEPLAY);
    }
  } else {
    button->color.a = 0xff - 0xff / 4;
  }
}

void scene_main_update(SceneMainObject *scene) {
  play_button_update(scene->play_button);
}

void scene_gameplay_draw(SceneGameplayObject *scene) {
  words_draw(scene->words);
  player_input_draw(scene->player_input);
  score_draw(scene->score);
}

void play_button_draw(PlayButton *button) {
  DrawText(button->text, button->x, button->y, button->font_size,
           button->color);
}

void scene_main_draw(SceneMainObject *scene) {
  DrawText(scene->title_text, scene->title_x, scene->title_y,
           scene->title_font_size, RAYWHITE);
  play_button_draw(scene->play_button);
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
