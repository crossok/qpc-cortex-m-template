#ifndef __BASE_BSP_H__
#define __BASE_BSP_H__

#include "base/common.h"

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
* Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
* DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
*/
enum KernelUnawareISRs {                                      /* see NOTE00 */
    /* ... */
    MAX_KERNEL_UNAWARE_CMSIS_PRI                        /* keep always last */
};
/* "kernel-unaware" interrupts can't overlap "kernel-aware" interrupts */
Q_ASSERT_COMPILE(MAX_KERNEL_UNAWARE_CMSIS_PRI <= QF_AWARE_ISR_CMSIS_PRI);

enum KernelAwareISRs {
    HIGH_IRQ_PRIORITY = QF_AWARE_ISR_CMSIS_PRI,                    /* see NOTE00 */
    MIDDLE_IRQ_PRIORITY,
    LOW_IRQ_PRIORITY,
    
    /* ... */
    MAX_KERNEL_AWARE_CMSIS_PRI                          /* keep always last */
};

#endif
