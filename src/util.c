#include "util.h"

#include <stdlib.h>
#include <string.h>

const char *to_bool_string(int b) {
  static const char *true_s = "true";
  static const char *false_s = "false";
  return b == 0 ? true_s : false_s;
}

char **split(char *str, size_t *size) {
  size_t len = strlen(str);
  size_t n_newlines = 0;

  // replace newlines with null characters
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == '\n') {
      str[i] = '\0';
      ++n_newlines;
    }
  }

  // allocate that amount
  char **pointers = malloc((n_newlines + 1) * sizeof(char **));

  // set first pointer to beginning of wordlist
  pointers[0] = &str[0];
  size_t pointers_size = 1;

  // set subsequent pointers to points after null chars
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == '\0') {
      pointers[pointers_size] = &str[i + 1];
      ++pointers_size;
    }
  }

  *size = pointers_size;

  return pointers;
}
