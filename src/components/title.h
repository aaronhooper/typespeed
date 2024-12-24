#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct Title {
  const char *text;
  int font_size;
  int x;
  int y;
  size_t text_hidden;
  bool is_animating;
  float anim_time_char_change;
  float anim_time_next_char;
  char anim_random_char;
  char *anim_text;
} Title;

Title *title_create();
void title_free(Title *title);
void title_update(Title *title);
void title_draw(Title *title);
