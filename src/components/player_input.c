#include "player_input.h"
#include "config.h"
#include "raylib.h"

#include <stdlib.h>
#include <string.h>

PlayerInput player_input_create() {
  // just assume we can alloc 20 bytes
  char *buffer = calloc(MAX_WORD_LENGTH, sizeof(char));

  PlayerInput player_input = {
      .buffer = buffer,
      .size = 0,
      .capacity = MAX_WORD_LENGTH,
  };

  return player_input;
}

void player_input_free(PlayerInput *player_input) {
  free(player_input->buffer);
  memset(player_input, 0, sizeof(PlayerInput));
}

void player_input_push_key(PlayerInput *player_input, char key) {
  player_input->buffer[player_input->size] = key;
  player_input->size++;
}

void player_input_pop_key(PlayerInput *player_input) {
  if (player_input->size != 0) {
    player_input->size--;
    player_input->buffer[player_input->size] = '\0';
  }
}

void player_input_clear(PlayerInput *player_input) {
  memset(player_input->buffer, 0, player_input->size);
  player_input->size = 0;
}

void player_input_draw(const PlayerInput *player_input) {
  DrawText(player_input->buffer, 0, GetScreenHeight() - 24, 24, RAYWHITE);
}
