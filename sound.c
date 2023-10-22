/*****************************************
  Mroczna Harmonia

  sound.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include "globals.h"

int sb_init(void)
{
    return 1;
}

void sb_dsp_out(unsigned char value)
{
}

void interrupt dma_int(void)
{
}

void enable_dma_int(void)
{
}

void disable_dma_int(void)
{
}

void convert_address(unsigned segment, unsigned off1,
    unsigned char* page, unsigned* off2)
{
}

void set_dma(unsigned char page, unsigned off, unsigned lenght)
{
}

void set_freq(unsigned freq)
{
}

void play_sound(SOUND* s)
{
}

unsigned get_file_size(char* filename)
{
    return 0;
}

int load_sound(SOUND* s, char* filename)
{
    return 1;
}

void unload_sound(SOUND* s)
{
}

void unload_sounds(void)
{
}
