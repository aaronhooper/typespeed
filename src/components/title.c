#include "title.h"
#include "config.h"
#include "raylib.h"

#include <stdlib.h>
#include <string.h>

#define ANIM_TIME_NEXT_CHAR 0.25f
#define ANIM_TIME_CHAR_CHANGE 0.05f

static const char *alpha =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@£$%^&*()-=_+";
static const size_t alpha_size = 66;

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

  title->is_animating = true;
  title->text_hidden = 0;
  title->anim_time_next_char = ANIM_TIME_NEXT_CHAR;
  title->anim_time_char_change = ANIM_TIME_CHAR_CHANGE;
  title->anim_random_char = 'a';
  title->anim_text = malloc(sizeof(title->text));

  return title;
}

void title_free(Title *title) {
  free(title->anim_text);
  free(title);
}

void title_update(Title *title) {
  strncpy(title->anim_text, title->text, title->text_hidden);
  title->anim_text[title->text_hidden] = title->anim_random_char;

  size_t text_len = strlen(title->text);

  if (title->text_hidden == text_len) {
    return;
  }

  float dt = GetFrameTime();
  title->anim_time_next_char -= dt;
  title->anim_time_char_change -= dt;

  if (title->anim_time_next_char < 0) {
    title->anim_time_next_char += ANIM_TIME_NEXT_CHAR;
    ++(title->text_hidden);
  }

  if (title->text_hidden == text_len) {
    title->anim_text[text_len] = title->text[text_len];
    return;
  }

  if (title->anim_time_char_change < 0) {
    title->anim_time_char_change = ANIM_TIME_CHAR_CHANGE;
    title->anim_random_char = alpha[rand() % alpha_size];
  }
}

void title_draw(Title *title) {
  DrawText(title->anim_text, title->x, title->y, title->font_size, RAYWHITE);
}
