#include "play_button.h"
#include "scene.h"

PlayButton *play_button_create(Arena *arena) {
  PlayButton *button = arena_alloc(arena, sizeof(PlayButton));

  button->text = "play";
  button->font_size = 36;

  // position button 100 pixels south of the screen center
  int play_button_width = MeasureText(button->text, button->font_size);
  int play_button_height = button->font_size;
  int play_button_x = (GetScreenWidth() / 2) - (play_button_width / 2);
  int play_button_y = (GetScreenHeight() / 2) - (play_button_height / 2) + 100;

  button->x = play_button_x;
  button->y = play_button_y;
  button->color.r = 0xff;
  button->color.g = 0xff;
  button->color.b = 0xff;
  button->color.a = 0xff - 0xff / 4;

  return button;
}

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
