#include "word.h"
#include "config.h"
#include "dict.h"
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(char *text, float x, float y) {
  Word *word = malloc(sizeof(Word));
  word->text = text;
  word->pos.x = x;
  word->pos.y = y;
  word->next = NULL;

  return word;
}

Word *word_create_random(Dict *dict) {
  char *rand_word = dict->words[GetRandomValue(0, dict->size - 1)];
  float rand_x = GetRandomValue(0, SCREEN_WIDTH);
  float rand_y = GetRandomValue(0, SCREEN_HEIGHT);

  return word_create(rand_word, rand_x, rand_y);
}

Word *words_create(Dict *dict, int n) {
  Word *head = word_create_random(dict);
  Word *curr = head;

  for (int i = 0; i < n - 1; ++i) {
    curr->next = word_create_random(dict);
    curr = curr->next;
  }

  return head;
}

void words_free(Word *head) {
  Word *curr = head;
  Word *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}

void words_update(Word *words) {
  for (Word *curr = words; curr != NULL; curr = curr->next) {
    curr->pos.y = curr->pos.y + 1;
  }
}

void words_draw(Word *words) {
  for (Word *curr = words; curr != NULL; curr = curr->next) {
    DrawText(curr->text, curr->pos.x, curr->pos.y, 24, GRAY);
  }
}

void words_foreach(Word *words, void (*fn)(Word *)) {
  for (Word *curr = words; curr != NULL; curr = curr->next) {
    fn(curr);
  }
}

void word_print(Word *word) { printf("%s\n", word->text); }
