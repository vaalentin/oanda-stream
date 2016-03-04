#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "utils.h"

int main(int argc, char* argv[]) {
  // config
  config_infos config = config_get(argc, argv);

  bool err = false;

  if(config.id == NULL) {
    err = true;
    fprintf(stderr, "Account id missing. Use -a flag\n");
  }

  if(config.tok == NULL) {
    err = true;
    fprintf(stderr, "Token missing. Use -t flag\n");
  }

  if(config.db_name == NULL) {
    config.db_name = str_dup("stream.sql");
  }

  if(config.n_instrs < 1) {
    err = true;
    fprintf(stderr, "Instrument missing. Use -i flag");
  }

  if(err) {
    exit(EXIT_FAILURE);
  }

  // clean
  config_delete(&config);

  return 0;
}
