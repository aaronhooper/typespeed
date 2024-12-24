#include "player_input.h"
#include "raylib.h"

#include <string.h>

void player_input_push_key(char *player_input, char key) {
  int len = strlen(player_input);
  player_input[len] = key;
  player_input[len + 1] = '\0';
}

void player_input_pop_key(char *player_input) {
  int len = strlen(player_input);

  if (len != 0) {
    player_input[len - 1] = '\0';
  }
}

void player_input_clear(char *player_input) {
  memset(player_input, 0, strlen(player_input));
  player_input[0] = '\0';
}

void player_input_draw(const char *player_input) {
  DrawText(player_input, 0, GetScreenHeight() - 24, 24, RAYWHITE);
}
