#pragma once

#include "memory/arena.h"
#include "raylib.h"

typedef struct PlayButton {
  const char *text;
  int font_size;
  Color color;
  int x;
  int y;
} PlayButton;

PlayButton *play_button_create(Arena *arena);
void play_button_update(PlayButton *button);
void play_button_draw(PlayButton *button);
