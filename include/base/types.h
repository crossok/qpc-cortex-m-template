#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

#include <stdio.h>
#include "base/config.h"

typedef struct timestamp_t
{
    uint64_t msec;
    uint32_t counter;           //SysTick counter register value
}timestamp_t;



#endif
