#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "db.h"

sqlite3* db_open(const char* name) {
  sqlite3* db;

  int res = sqlite3_open(name, &db);

  if(res != SQLITE_OK) {
    printf("%s\n", sqlite3_errmsg(db));
    exit(1);
  }

  return db;
}

void db_create_tables(sqlite3* db) {
  const char* sql_query = "CREATE TABLE IF NOT EXISTS prices(" \
                           "id INTEGER PRIMARY KEY," \
                           "instrument CHAR(10)," \
                           "time DATE,"
                           "bid REAL," \
                           "ask REAL)";

  char* err_msg = NULL;

  int res = sqlite3_exec(db, sql_query, NULL, 0, &err_msg);

  if(res != SQLITE_OK) {
    printf("%s\n", err_msg);
    exit(1);
  }
}

void db_close(sqlite3* db) {
  sqlite3_close(db);
}
