#include <stdio.h>
#include <string.h>
#include <json.h>

#include "heartbeat.h"

heartbeat_infos heartbeat_get(json_value* val) {
  heartbeat_infos heartbeat;

  size_t n_vals = val->u.object.length;

  for(size_t i = 0; i < n_vals; ++i) {
    char* key = val->u.object.values[i].name;
    json_value* child_val = val->u.object.values[i].value;

    if(strcmp(key, "time") == 0) {
      heartbeat.time = child_val->u.string.ptr;
    }
  }

  return heartbeat;
}

void heartbeat_log(heartbeat_infos* heartbeat) {
  printf("time: %s\n", heartbeat->time);
}
