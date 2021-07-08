#ifndef __BASE_KB_H__
#define __BASE_KB_H__

#include "base/common.h"

void kb_init(void);
void kb_scan(void);
void kb_dispatch_event(uint8_t id, uint8_t state);

#endif
