#ifndef H_DB
#define H_DB

#include <sqlite3.h>

sqlite3* db_open(const char* name);
void db_create_tables(sqlite3* db);
void db_close(sqlite3* db);

#endif
