/*****************************************
  Mroczna Harmonia

  clock.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <dos.h>

#include "globals.h"

void interrupt (*old_clock_interrupt)(void);

const unsigned long clock_frequency = 1193181;
const unsigned long dos_divisor = 65535; 

// timer factor: how many times faster than regular timer (f * 18.02/s)
const unsigned long timer_factor = 15;
const unsigned long my_divisor = 4369; 

unsigned long timer = 0, timer_stop;


void timer_start(unsigned long ticks)
{
    timer_stop = timer + ticks;
}

void timer_wait()
{
    while (timer < timer_stop)
        ;
}

void interrupt clock_interrupt(void)
{
    if ((++timer) % timer_factor == 0) {
        old_clock_interrupt();
    }
}

void clock_init(void)
{
    old_clock_interrupt = getvect(0x1c);
    setvect(0x1c, clock_interrupt);
	
    outportb(0x43, 0x34);

    outportb(0x40, (unsigned char)(my_divisor & 0xff));
    outportb(0x40, (unsigned char)((my_divisor >> 8) & 0xff));
}

void clock_shutdown(void)
{
    setvect(0x1c, old_clock_interrupt);
    
    outportb(0x43, 0x34);
    outportb(0x40, -1);
    outportb(0x40, -1);
}
