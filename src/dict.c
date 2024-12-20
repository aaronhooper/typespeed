#include "dict.h"
#include "raylib.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dict dict_load(const char *filename) {
  char *buffer = LoadFileText(filename);
  size_t wordlist_size;
  char **words = split(buffer, &wordlist_size);

  Dict dict = {
      .words = words,
      .size = wordlist_size,
      .buffer = buffer,
  };

  return dict;
}

void dict_free(Dict *dict) {
  free(dict->words);
  UnloadFileText(dict->buffer);
  memset(dict, 0, sizeof(Dict));
}
