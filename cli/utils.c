#include <stdlib.h>
#include <string.h>

#include "utils.h"

char* str_dup(char* in) {
  size_t n_chars = strlen(in);
  char* out = (char*) malloc(n_chars * sizeof(char) + 1);
  strcpy(out, in);
  return out;
}
