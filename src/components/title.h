#pragma once

#include "memory/arena.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct Title {
  const char *text;
  size_t text_len;
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

Title *title_create(Arena *arena);
void title_update(Title *title);
void title_draw(Title *title);
