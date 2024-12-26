#include "word.h"
#include "config.h"
#include "memory/arena.h"
#include "memory/slab.h"
#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(Slab *slab, char *text, float x, float y) {
  Word *word;

  if ((word = slab_alloc(slab)) == NULL) {
    return NULL;
  }

  word->text = text;
  word->pos.x = x;
  word->pos.y = y;
  word->next = NULL;

  return word;
}

Word *word_create_random(Slab *slab, Dict *dict) {
  char *rand_word = dict->words[GetRandomValue(0, dict->size - 1)];
  float rand_x = GetRandomValue(0, GetScreenWidth());
  float rand_y = GetRandomValue(0, GetScreenHeight());

  return word_create(slab, rand_word, rand_x, rand_y);
}

Word *words_create(Arena *arena, Slab *slab, Dict *dict, int n) {
  assert(n > 0);

  if (slab_init(slab, arena, sizeof(Word), n) == NULL) {
    return NULL;
  }

  Word *head = word_create_random(slab, dict);
  Word *curr = head;

  for (int i = 0; i < n - 1; ++i) {
    curr->next = word_create_random(slab, dict);
    curr = curr->next;
  }

  return head;
}

Word *words_add_random(Slab *slab, Word *word, Dict *dict) {
  Word *new = word_create_random(slab, dict);
  new->next = word;

  return new;
}

bool words_remove(Slab *slab, Word **word, const char *match) {
  Word *head = *word, *curr = *word, *prev;
  bool is_match = strncmp(curr->text, match, MAX_WORD_LENGTH) == 0;

  if (is_match) {
    *word = curr->next;
    slab_free(slab, curr);
    return true;
  }

  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
    is_match = strncmp(curr->text, match, MAX_WORD_LENGTH) == 0;

    if (is_match) {
      prev->next = curr->next;
      *word = head;
      slab_free(slab, curr);
      return true;
    }
  }

  *word = head;
  return false;
}

void words_update(Word *words) {
  float dt = GetFrameTime();
  Word *curr = words;

  while (curr != NULL) {
    curr->pos.y = curr->pos.y + 1 * dt;
    curr = curr->next;
  }
}

void words_draw(Word *words) {
  for (Word *curr = words; curr != NULL; curr = curr->next) {
    DrawText(curr->text, curr->pos.x, curr->pos.y, 24, RAYWHITE);
  }
}

void words_foreach(Word *words, void (*fn)(Word *)) {
  for (Word *curr = words; curr != NULL; curr = curr->next) {
    fn(curr);
  }
}

void word_print(Word *word) { printf("%s\n", word->text); }

size_t words_len(Slab *slab) { return slab->size; }
