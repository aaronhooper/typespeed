#include "util.h"
#include "config.h"
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *to_bool_string(int b) {
  static const char *true_s = "true";
  static const char *false_s = "false";
  return b == 0 ? true_s : false_s;
}

char **split(char *str, size_t *size) {
  size_t len = strlen(str);
  size_t n_newlines = 0;

  // replace newlines with null characters
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == '\n') {
      str[i] = '\0';
      ++n_newlines;
    }
  }

  // allocate that amount
  char **pointers = malloc((n_newlines + 1) * sizeof(char **));

  // set first pointer to beginning of wordlist
  pointers[0] = str;
  size_t pointers_size = 1;

  // set pointers to the address after the null char
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == '\0') {
      pointers[pointers_size] = &str[i + 1];
      ++pointers_size;
    }
  }

  *size = pointers_size;

  return pointers;
}

void fps_draw() {
  char buffer[15];
  snprintf(buffer, sizeof(buffer), "FPS: %d", GetFPS());
  int font_size = 16;
  int text_width = MeasureText(buffer, font_size);
  DrawText(buffer, (SCREEN_WIDTH / 2) - (text_width / 2), 0, font_size, GRAY);
}

void score_draw(int score) {
  const size_t len = 18;
  char text[len];
  snprintf(text, len, "Score: %d", score);
  DrawText(text, 0, 0, 24, BATTLESHIP_GRAY);
}
