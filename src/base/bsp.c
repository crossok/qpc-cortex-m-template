#include "base/base.h"

#include "base/bsp.h"

/* "kernel-aware" interrupts should not overlap the PendSV priority */
Q_ASSERT_COMPILE(MAX_KERNEL_AWARE_CMSIS_PRI <= (0xFF >> (8 - __NVIC_PRIO_BITS)));

/*..........................................................................*/
void SysTick_Handler(void) {                       /* system clock tick ISR */
    QF_TICK_X(0U, (void *)0);              /* process all armed time events */
    
    /* we do not call HAL_Init() function, so tick is managed by QPC */
    HAL_IncTick();
}


/*..........................................................................*/
void QF_onStartup(void) {
    
    /* 1. Enable basic clocks: SYSCFG_CLK & PWR_CLK, then we can read/write registers*/
    HAL_MspInit();
    
    /* 2. System Clock Configuration */
    SystemClock_Config();
    
    /* 3. Configure other peripherals */
    gpio_init();
    led_init();
    uart_init();
    
    /* 4 Start SysTick timer*/
    SysTick_Config(SystemCoreClock / QF_TICKS_PER_SEC);

    /* set priorities of ALL ISRs used in the system, see NOTE00
    *
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    * Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    * DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    */
    NVIC_SetPriority(SysTick_IRQn, LOW_IRQ_PRIORITY);
    /* ... */
    /* enable IRQs... */
}            
/*..........................................................................*/
void QF_onCleanup(void) {
}

//#define NDEBUG
/*..........................................................................*/
void QF_onIdle(void) {       /* called with interrupts disabled, see NOTE01 */
#ifdef NDEBUG
    /* Put the CPU and peripherals to the low-power mode.
    * you might need to customize the clock management for your application,
    * see the datasheet for your particular Cortex-M MCU.
    */
    QV_CPU_SLEEP();         /* atomically go to sleep and enable interrupts */
    
#else
    QF_INT_ENABLE();                              /* just enable interrupts */
#endif
}

/*..........................................................................*/
void Q_onAssert(char_t const * const module, int_t location){
    //assert_failed(file, line);
}

/*****************************************************************************
* NOTE00:
* The QF_AWARE_ISR_CMSIS_PRI constant from the QF port specifies the highest
* ISR priority that is disabled by the QF framework. The value is suitable
* for the NVIC_SetPriority() CMSIS function.
*
* Only ISRs prioritized at or below the QF_AWARE_ISR_CMSIS_PRI level (i.e.,
* with the numerical values of priorities equal or higher than
* QF_AWARE_ISR_CMSIS_PRI) are allowed to call any QF services. These ISRs
* are "QF-aware".
*
* Conversely, any ISRs prioritized above the QF_AWARE_ISR_CMSIS_PRI priority
* level (i.e., with the numerical values of priorities less than
* QF_AWARE_ISR_CMSIS_PRI) are never disabled and are not aware of the kernel.
* Such "QF-unaware" ISRs cannot call any QF services. The only mechanism
* by which a "QF-unaware" ISR can communicate with the QF framework is by
* triggering a "QF-aware" ISR, which can post/publish events.
*
* NOTE01:
* The QF_onIdle() callback is called with interrupts disabled, because the
* determination of the idle condition might change by any interrupt posting
* an event. QF::onIdle() must internally enable interrupts, ideally
* atomically with putting the CPU to the power-saving mode.
*/
