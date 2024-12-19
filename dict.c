#include "dict.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dict *dict_load(const char *filename, size_t n) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error: Could not open the dict file\n");
    exit(EXIT_FAILURE);
  }

  char *strings_buf = malloc(n * (MAX_WORD_LENGTH + 1) * sizeof(char));
  Dict *dict = malloc(sizeof(Dict) + n * sizeof(char *));
  dict->size = 0;
  dict->capacity = n;
  dict->ptr = strings_buf;

  char scan_buf[MAX_WORD_LENGTH + 1];

  for (size_t i = 0; i < n && fscanf(fp, "%s", scan_buf) == 1; ++i) {
    char *string_ptr = &strings_buf[i * (MAX_WORD_LENGTH + 1)];
    strncpy(string_ptr, scan_buf, MAX_WORD_LENGTH);
    string_ptr[MAX_WORD_LENGTH] = '\0';

    dict->words[i] = string_ptr;
    dict->size++;
  }

  fclose(fp);
  return dict;
}

void dict_free(Dict *dict) {
  free(dict->ptr);
  free(dict);
}
