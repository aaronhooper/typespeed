#include "title.h"
#include "config.h"
#include "memory/arena.h"
#include "raylib.h"

#include <stdlib.h>
#include <string.h>

#define ANIM_TIME_NEXT_CHAR 0.25f
#define ANIM_TIME_CHAR_CHANGE 0.05f

static const char *alpha =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@£$%^&*()-=_+";
static const size_t alpha_size = 66;

Title *title_create(Arena *arena) {
  Title *title = arena_alloc(arena, sizeof(Title));
  title->text = WINDOW_TITLE;
  title->text_len = strlen(title->text);
  title->font_size = 48;

  // position title at the screen center
  int title_width = MeasureText(title->text, title->font_size);
  int title_height = title->font_size;
  int title_x = (GetScreenWidth() / 2) - (title_width / 2);
  int title_y = (GetScreenHeight() / 2) - (title_height / 2);

  title->x = title_x;
  title->y = title_y;
  title->is_animating = true;
  title->text_hidden = 0;
  title->anim_time_next_char = ANIM_TIME_NEXT_CHAR;
  title->anim_time_char_change = ANIM_TIME_CHAR_CHANGE;
  title->anim_random_char = 'a';
  title->anim_text = arena_alloc(arena, title->text_len * sizeof(char));
  memset(title->anim_text, 0, title->text_len);

  return title;
}

void title_animate_typing(Title *title) {
  strncpy(title->anim_text, title->text, title->text_hidden);
  title->anim_text[title->text_hidden] = title->anim_random_char;

  float dt = GetFrameTime();
  title->anim_time_next_char -= dt;
  title->anim_time_char_change -= dt;

  if (title->anim_time_next_char < 0) {
    title->anim_time_next_char += ANIM_TIME_NEXT_CHAR;
    title->text_hidden++;
  }

  if (title->text_hidden == title->text_len) {
    title->anim_text[title->text_len - 1] = title->text[title->text_len - 1];
    title->is_animating = false;
    return;
  }

  if (title->anim_time_char_change < 0) {
    title->anim_time_char_change = ANIM_TIME_CHAR_CHANGE;
    title->anim_random_char = alpha[rand() % alpha_size];
  }
}

void title_update(Title *title) {
  if (title->is_animating) {
    title_animate_typing(title);
  }
}

void title_draw(Title *title) {
  DrawText(title->anim_text, title->x, title->y, title->font_size, RAYWHITE);
}
