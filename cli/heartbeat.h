#ifndef H_HEARTBEAT
#define H_HEARTBEAT

#include <json.h>

typedef struct heartbeat_infos {
  char* time;
} heartbeat_infos;

heartbeat_infos heartbeat_get(json_value* val);
void heartbeat_log(heartbeat_infos* heartbeat);

#endif
