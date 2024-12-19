#pragma once

#include "dict.h"
#include "raylib.h"

typedef struct Word Word;

struct Word {
  Word *next;
  char *text;
  Vector2 pos;
};

Word *word_create(char *text, float x, float y);
Word *word_create_random(Dict *dict);
void word_print(Word *word);
Word *words_create(Dict *dict, int n);
void words_free(Word *head);
void words_update(Word *words);
void words_draw(Word *words);
void words_foreach(Word *words, void (*fn)(Word *));