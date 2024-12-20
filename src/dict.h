#pragma once

#include <stddef.h>

typedef struct {
  size_t size;
  size_t capacity;
  char *ptr;
  char *words[];
} Dict;

Dict *dict_load(const char *filename, size_t n);
void dict_free(Dict *dict);
