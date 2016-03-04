#include <string.h>

#include "config.h"
#include "utils.h"

config_infos config_get(int argc, char* argv[]) {
  config_infos config = {.id = NULL, .tok = NULL, .instrs = NULL, .n_instrs = 0, .db_name = NULL};

  for(int i = 0, j = 1; i < argc; ++i, ++j) {
    char* arg = argv[i];
    if(strcmp(arg, "-a") == 0) {
      if(j < argc && *argv[j] != '-') {
        config.id = str_dup(argv[j]);
      }
    }
    else if(strcmp(arg, "-t") == 0) {
      if(j < argc && *argv[j] != '-') {
        config.tok = str_dup(argv[j]);
      }
    }
    else if(strcmp(arg, "-d") == 0) {
      if(j < argc && *argv[j] != '-') {
        config.db_name = str_dup(argv[j]);
      }
    }
    else if(strcmp(arg, "-i") == 0) {
      int to = j;

      while(to < argc && *argv[to] != '-') {
        ++to;
      }

      config.n_instrs = to - j;
      config.instrs = (char**) malloc(config.n_instrs * sizeof(char*));

      for(size_t i = 0; i < config.n_instrs; ++i) {
        config.instrs[i] = str_dup(argv[j + i]);
      }
    }
  }

  return config;
}

void config_delete(config_infos* config) {
  free(config->id);

  free(config->tok);

  free(config->db_name);

  for(size_t i = 0; i < config->n_instrs; ++i) {
    free(config->instrs[i]);
  }

  free(config->instrs);
}
