#pragma once

#include <stddef.h>

typedef struct PlayerInput {
  char *buffer;
  size_t size;
  size_t capacity;
} PlayerInput;

PlayerInput player_input_create();
void player_input_free(PlayerInput *player_input);
void player_input_push_key(PlayerInput *player_input, char key);
void player_input_pop_key(PlayerInput *player_input);
void player_input_clear(PlayerInput *player_input);
void player_input_draw(const PlayerInput *player_input);
