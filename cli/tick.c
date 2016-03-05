#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <json.h>

#include "tick.h"

tick_infos tick_get(json_value* val) {
  tick_infos tick;

  size_t n_vals = val->u.object.length;

  for(size_t i = 0; i < n_vals; ++i) {
    char* key = val->u.object.values[i].name;
    json_value* child_val = val->u.object.values[i].value;

    if(strcmp(key, "instrument") == 0) {
      tick.pair = child_val->u.string.ptr;
    }
    else if(strcmp(key, "time") == 0) {
      tick.time = child_val->u.string.ptr;
    }
    else if(strcmp(key, "bid") == 0) {
      tick.bid = &child_val->u.dbl;
    }
    else if(strcmp(key, "ask") == 0) {
      tick.ask = &child_val->u.dbl;
    }
  }

  return tick;
}

void tick_log(tick_infos* tick) {
  printf("%s, time: %s, bid: %f, ask: %f\n", tick->pair, tick->time, *(tick->bid), *(tick->ask));
}

void tick_save(sqlite3* db, tick_infos* tick) {
  char sql_query[100];

  snprintf(sql_query, 100, "INSERT INTO prices VALUES(NULL,'%s','%s',%f,%f)", tick->pair, tick->time, *(tick->bid), *(tick->ask));

  char* err_msg = NULL;

  int res = sqlite3_exec(db, sql_query, NULL, 0, &err_msg);

  if(res != SQLITE_OK) {
    printf("%s\n", err_msg);
  }
  else {
    printf("OK: %s\n", sql_query);
  }
}
