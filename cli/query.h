#ifndef H_QUERY
#define H_QUERY

#include <stdlib.h>

char* query_get_auth_header(const char* tok);
char* query_get_instrs(char** instrs, size_t n_instrs);
char* query_get_url(char* id, char* instrs);

#endif
