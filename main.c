#include "msp.h"
#include "bsp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Inits the entire board
	BSP_InitBoard();
}
