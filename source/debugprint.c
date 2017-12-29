#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

//Only works in no$gba
//
//The ascii string may contain parameters, defined as %param%.
//  r0,r1,r2,...,r15  show register content (displayed as 32bit Hex number)
//  sp,lr,pc          alias for r13,r14,r15
//  scanline          show current scanline number
//  frame             show total number of frames since coldboot
//  totalclks         show total number of clock cycles since coldboot
//  lastclks          show number of cycles since previous lastclks (or zeroclks)
//  zeroclks          resets the 'lastclks' counter
void debugPrint(char *str)
{
    *(volatile u32*)0x4FFFA18 = (u32)str;
}