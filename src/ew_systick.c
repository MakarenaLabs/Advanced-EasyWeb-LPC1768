#include "LPC17xx.h"

extern void TCPClockHandler(void);

volatile uint32_t TimeTick = 0;
volatile uint32_t TimeTick2 = 0;


// ****************
//  SysTick_Handler
void SysTick_Handler(void)
{
	TimeTick++;		// Increment first SysTick counter
	TimeTick2++;	// Increment second SysTick counter
	
	// After 100 ticks (100 x 10ms = 1sec)
	if (TimeTick >= 1000) {
	  TimeTick = 0;	// Reset counter
	}
	// After 20 ticks (20 x 10ms = 1/5sec)
	if (TimeTick2 >= 10) {
	  TimeTick2 = 0; // Reset counter
	  TCPClockHandler();  // Call TCP handler
	}
}

// ****************
// Setup SysTick Timer to interrupt at 10 msec intervals
void Start_SysTick10ms(void)
{
	if (SysTick_Config(SystemCoreClock / 100)) {
		while (1);  // Capture error
	}
}
