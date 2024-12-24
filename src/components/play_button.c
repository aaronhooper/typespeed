#include "play_button.h"
#include "scene.h"

#include <stdlib.h>

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
