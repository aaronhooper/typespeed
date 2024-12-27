#include "arena.h"

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void *arena_init(Arena *arena, size_t capacity) {
  void *buffer =
      mmap(NULL, capacity * sizeof(unsigned char), PROT_READ | PROT_WRITE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (buffer == NULL) {
    return NULL;
  }

  arena->size = 0;
  arena->capacity = capacity;
  arena->buffer = buffer;

  return buffer;
}

void *arena_alloc(Arena *arena, size_t requested_size) {
  void *ptr = (unsigned char *)arena->buffer + arena->size;
  arena->size += requested_size;
  return ptr;
}

void arena_flush(Arena *arena) { arena->size = 0; }

void arena_free(Arena *arena) {
  munmap(arena->buffer, arena->capacity);
  memset(arena, 0, sizeof(Arena));
}
