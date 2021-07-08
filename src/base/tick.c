#include "base/tick.h"

typedef struct tick_t
{
    uint64_t msec;
    
    uint32_t cycles_in_msec;
}tick_t;

static tick_t l_tick;

void tick_init(void)
{
    QF_bzero(&l_tick, sizeof(l_tick));
    
    LOG("SystemCoreClock :%d", SystemCoreClock );
    
    l_tick.cycles_in_msec = SystemCoreClock / QF_TICKS_PER_SEC;
}

void tick_cb(void)
{
    ++l_tick.msec;
}

void tick_get_timestamp(timestamp_t *ts)
{
    ts->msec = l_tick.msec;
    ts->counter = l_tick.cycles_in_msec - SysTick->VAL;
}

uint32_t tick_elapsed_msec(timestamp_t *start, timestamp_t *stop)
{
    uint32_t msec = stop->msec - start->msec;

    return msec;
}

uint32_t tick_elapsed_usec(timestamp_t *start, timestamp_t *stop)
{
    uint32_t msec = stop->msec - start->msec;
    int32_t  cycle = stop->counter - start->counter;
    LOG("cycle:%d", cycle);

    msec = msec * 1000 + cycle/48;

    return msec;
}

uint32_t tick_elapsed_cycle(timestamp_t *start, timestamp_t *stop)
{
    uint32_t msec = stop->msec - start->msec;
    int32_t  cycle = stop->counter - start->counter;

    msec = msec * 48000 + cycle;

    return msec;
}

uint32_t tick_elapsed_nanosec(timestamp_t *start, timestamp_t *stop)
{
    uint32_t msec = stop->msec - start->msec;

    return msec;
}
