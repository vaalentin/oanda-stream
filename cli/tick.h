#ifndef H_TICK
#define H_TICK

#include <sqlite3.h>
#include <json.h>

typedef struct tick_infos {
  char* pair;
  char* time;
  double* bid;
  double* ask;
} tick_infos;

tick_infos tick_get(json_value* val);
void tick_log(tick_infos* tick);
void tick_save(sqlite3* db, tick_infos* tick);

#endif
