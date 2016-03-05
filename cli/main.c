#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>

#include "db.h"
#include "query.h"
#include "config.h"
#include "utils.h"

sqlite3* db = NULL;

size_t handle_chunk(void* buffer, size_t size, size_t nmemb, void* userp) {
  printf("%s\n", (char*) buffer);
  return size * nmemb;
}

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

  // query
  CURL* handle = curl_easy_init();

  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, auth_header);

  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_easy_setopt(handle, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, handle_chunk);
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

  CURLcode res = curl_easy_perform(handle);

  if(res != CURLE_OK) {
    printf("%s\n", curl_easy_strerror(res));
    exit(EXIT_FAILURE);
  }

  // clean
  free(headers);
  curl_easy_cleanup(handle);
  free(instrs_query);
  free(url);
  free(auth_header);
  config_delete(&config);
  db_close(db);

  return 0;
}
