#pragma once

#include <stddef.h>

typedef struct {
  size_t size;
  char *buffer;
  char **words;
} Dict;

Dict dict_load(const char *filename);
void dict_free(Dict dict);
