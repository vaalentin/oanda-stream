#ifndef H_CONFIG
#define H_CONFIG

#include <stdlib.h>

typedef struct config_infos {
  char* id;
  char* tok;
  char** instrs;
  size_t n_instrs;
  char* db_name;
} config_infos;

config_infos config_get(int argc, char* argv[]);
void config_delete(config_infos* config);

#endif
