#include "title.h"
#include "config.h"

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

void title_draw(Title *title) {
  DrawText(title->text, title->x, title->y, title->font_size, RAYWHITE);
}
