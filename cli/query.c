#include <string.h>

#include "query.h"

char* query_get_auth_header(const char* tok) {
  const char* base = "Authorization: Bearer ";

  size_t n_chars = strlen(base) + strlen(tok) + 1;
  char* header = (char*) malloc(n_chars * sizeof(char));

  strcpy(header, base);
  strcat(header, tok);

  return header;
}

char* query_get_instrs(char** instrs, size_t n_instrs) {
  const char* sep = "%2C";
  size_t sep_len = strlen(sep);

  size_t n_chars = 1;

  for(size_t i = 0; i < n_instrs; ++i) {
    n_chars += strlen(instrs[i]);
    if(i != 0) n_chars += sep_len;
  }

  char* pairs_query = (char*) malloc(n_chars * sizeof(char));

  pairs_query[0] = '\0';

  for(size_t i = 0; i < n_instrs; ++i) {
    if(i != 0) strcat(pairs_query, sep);
    strcat(pairs_query, instrs[i]);
  }

  return pairs_query;
}

char* query_get_url(char* id, char* instrs) {
  const char* base = "https://stream-fxpractice.oanda.com/v1/prices?accountId=";
  const char* param = "&instruments=";

  size_t n_chars = strlen(base) + strlen(id) + strlen(param) + strlen(instrs);
  char* url = (char*) malloc(n_chars * sizeof(char) + 1);

  strcpy(url, base);
  strcat(url, id);
  strcat(url, param);
  strcat(url, instrs);

  return url;
}
