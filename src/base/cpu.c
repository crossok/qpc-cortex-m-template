#include "base/cpu.h"

void cpu_reset()
{
    NVIC_SystemReset();
}
