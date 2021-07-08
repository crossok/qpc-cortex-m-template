#ifndef __BASE_TICK_H__
#define __BASE_TICK_H__

#include "base/common.h"

void tick_get_timestamp(timestamp_t *ts);
uint32_t tick_elapsed_msec(timestamp_t *start, timestamp_t *stop);
uint32_t tick_elapsed_usec(timestamp_t *start, timestamp_t *stop);
uint32_t tick_elapsed_cycle(timestamp_t *start, timestamp_t *stop);
uint32_t tick_elapsed_nanosec(timestamp_t *start, timestamp_t *stop);

#endif
