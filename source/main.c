
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_timers.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameboy.h"

//---------------------------------------------------------------------------------
void VblankInterrupt()
//---------------------------------------------------------------------------------
{
    VBlank_Interrupt_Handler();
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);
    
    irqSet( IRQ_VBLANK, VblankInterrupt);
    
    //Init timers
    REG_TM2CNT_L = 0;
    REG_TM2CNT_H = TIMER_START | TIMER_DIV_1024;   // we're using the 1024 cycle timer

	//consoleDemoInit();

	// ansi escape sequence to set print co-ordinates
	// /x1b[line;columnH
	//iprintf("\x1b[10;10HHello World!\n");
    
    //for(int i=0; i<60*3; i++)
    //    VBlankIntrWait();
    
    GB_Init();

	while (1) {
		VBlankIntrWait();
	}
}


