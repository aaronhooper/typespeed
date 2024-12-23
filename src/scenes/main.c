#include "main.h"
#include "../config.h"
#include "../scene.h"
#include "raylib.h"

#include <stdlib.h>

Title *title_create() {
  Title *title = malloc(sizeof(Title));
  title->text = WINDOW_TITLE;
  title->font_size = 48;

  // get center coords of screen
  int screen_center_x = GetScreenWidth() / 2;
  int screen_center_y = GetScreenHeight() / 2;

  // set the text top left corner to the screen center
  int title_x = screen_center_x;
  int title_y = screen_center_y;

  // subtract text midpoint from x and y pos of text to
  // get the centered position
  int title_width = MeasureText(title->text, title->font_size);
  int title_height = title->font_size;
  title_x = title_x - (title_width / 2);
  title_y = title_y - (title_height / 2);

  title->x = title_x;
  title->y = title_y;

  return title;
}

void title_free(Title *title) { free(title); }

PlayButton *play_button_create() {
  PlayButton *button = malloc(sizeof(PlayButton));

  int screen_center_x = GetScreenWidth() / 2;
  int screen_center_y = GetScreenHeight() / 2;

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

void play_button_free(PlayButton *button) { free(button); }

void play_button_update(PlayButton *button) {
  int xstart = button->x;
  int xend = MeasureText(button->text, button->font_size) + xstart;
  int ystart = button->y;
  int yend = button->font_size + ystart;
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

void play_button_draw(PlayButton *button) {
  DrawText(button->text, button->x, button->y, button->font_size,
           button->color);
}

SceneMainObject *scene_main_create() {
  SceneMainObject *object = malloc(sizeof(SceneMainObject));
  object->title = title_create();
  object->play_button = play_button_create();

  return object;
}

void scene_main_free(SceneMainObject *object) {
  play_button_free(object->play_button);
  title_free(object->title);
  free(object);
}

void scene_main_update(SceneMainObject *scene) {
  play_button_update(scene->play_button);
}

void title_draw(Title *title) {
  DrawText(title->text, title->x, title->y, title->font_size, RAYWHITE);
}

void scene_main_draw(SceneMainObject *scene) {
  title_draw(scene->title);
  play_button_draw(scene->play_button);
}
