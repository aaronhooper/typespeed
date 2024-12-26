#pragma once

#include "dict.h"
#include "memory/arena.h"
#include "memory/slab.h"
#include "raylib.h"

#include <stdbool.h>

typedef struct Word Word;

struct Word {
  Word *next;
  char *text;
  Vector2 pos;
};

Word *word_create(Slab *slab, char *text, float x, float y);
Word *word_create_random(Slab *slab, Dict *dict);
void word_print(Word *word);

Word *words_create(Arena *arena, Slab *slab, Dict *dict, int n);
Word *words_add_random(Slab *slab, Word *word, Dict *dict);
bool words_remove(Slab *slab, Word **word, const char *match);
void words_update(Word *words);
void words_draw(Word *words);
void words_foreach(Word *words, void (*fn)(Word *));
size_t words_len(Slab *slab);
