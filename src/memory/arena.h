#pragma once

#include <stddef.h>

typedef struct Arena {
  size_t size;
  size_t capacity;
  void *buffer;
} Arena;


void *arena_init(Arena *arena, size_t capacity);
void *arena_alloc(Arena *arena, size_t requested_size);
void arena_flush(Arena *arena);
void arena_free(Arena *arena);
