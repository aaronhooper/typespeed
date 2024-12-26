#include "slab.h"
#include "arena.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Slab *slab_init(Slab *slab, Arena *arena, size_t block_size, size_t n_blocks) {
  if (block_size < sizeof(size_t)) {
    return NULL;
  }

  if ((slab->buffer = arena_alloc(arena, n_blocks * block_size)) == NULL) {
    return NULL;
  }

  slab->size = 0;
  slab->capacity = n_blocks;
  slab->block_size = block_size;
  slab->free = slab->buffer;
  SlabBlock *current = slab->free;

  // init the freelist
  for (size_t i = 0; i < n_blocks - 1; ++i) {
    // store the pointer to the next free block in the current free block
    current->next = (SlabBlock *)((unsigned char *)current + block_size);
    current = current->next;
  }

  current->next = NULL;

  return slab;
}

void *slab_alloc(Slab *slab) {
  if (slab->free == NULL) {
    return NULL;
  }

  slab->size++;
  void *alloc = slab->free;
  slab->free = slab->free->next;

  return alloc;
}

void slab_free(Slab *slab, void *block) {
  slab->size--;
  SlabBlock *dealloc = (SlabBlock *)block;
  dealloc->next = slab->free;
  slab->free = dealloc;
}
