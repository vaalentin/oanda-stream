#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "db.h"
#include "query.h"
#include "config.h"
#include "utils.h"

sqlite3* db = NULL;

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

  // db
  db = db_open(config.db_name);
  db_create_tables(db);

  // prepare query
  char* instrs_query = query_get_instrs(config.instrs, config.n_instrs);
  char* url = query_get_url(config.id, instrs_query);
  char* auth_header = query_get_auth_header(config.tok);

  // clean
  free(instrs_query);
  free(url);
  free(auth_header);
  config_delete(&config);
  db_close(db);

  return 0;
}
