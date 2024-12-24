#pragma once

typedef struct Title {
  const char *text;
  int font_size;
  int x;
  int y;
} Title;

Title *title_create();
void title_free(Title *title);
void title_draw(Title *title);
