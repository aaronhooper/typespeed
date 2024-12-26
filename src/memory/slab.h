#pragma once

#include "arena.h"

typedef struct SlabBlock SlabBlock;
typedef struct SlabBlock {
  SlabBlock *next;
} SlabBlock;

typedef struct Slab {
  size_t size;
  size_t capacity;
  size_t block_size;
  SlabBlock *free;
  void *buffer;
} Slab;

Slab *slab_init(Slab *slab, Arena *arena, size_t block_size, size_t n_blocks);
void *slab_alloc(Slab *slab);
void slab_free(Slab *slab, void *block);
