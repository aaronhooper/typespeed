#include "arena.h"

#include <stdlib.h>
#include <string.h>

void *arena_init(Arena *arena, size_t capacity) {
  void *buffer = malloc(capacity * sizeof(char));

  if (buffer == NULL) {
    return NULL;
  }

  arena->size = 0;
  arena->capacity = capacity;
  arena->buffer = buffer;

  return buffer;
}

void *arena_alloc(Arena *arena, size_t requested_size) {
  if (arena->size + requested_size >= arena->capacity) {
    size_t new_capacity = arena->capacity;

    // double the size of the buffer until it can hold the requested size
    do {
      new_capacity *= 2;
    } while (arena->size + requested_size >= new_capacity);

    void *new_buffer = realloc(arena->buffer, new_capacity * sizeof(char));

    if (new_buffer == NULL) {
      return NULL;
    }

    arena->buffer = new_buffer;
    arena->capacity = new_capacity;
  }

  void *ptr = (char *)arena->buffer + arena->size;
  arena->size += requested_size;
  return ptr;
}

void arena_flush(Arena *arena) { arena->size = 0; }

void arena_free(Arena *arena) {
  free(arena->buffer);
  memset(arena, 0, sizeof(Arena));
}
