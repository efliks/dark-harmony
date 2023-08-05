/*****************************************
  Mroczna Harmonia

  sound.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

#define SB_BASE_ADDRESS 0x220
#define DSP_OUT 0x10

#define DMA_CHANNEL 0x01
#define DMA_PAGE_PORT 0x83
#define DMA_OFFSET_PORT 0x02
#define DMA_LENGHT_PORT 0x03
#define DMA_MODE 0x48
#define DMA_INT 0x0d

#define WAV_HEADER_SIZE 44
#define SOUND_FREQUENCY 11025

void interrupt (*old_dma_int)(void);
unsigned char end_of_sound = 1;

int num_of_loaded_sounds = 0;


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
    FILE* p;
    unsigned size = 0;

    if ((p = fopen(filename, "r+b")) == NULL)
        return NULL;

    while (!feof(p)) {
        fgetc(p);
        size++;
    }

    fclose(p);
    return size;
}

int load_sound(SOUND* s, char* filename)
{
    FILE* p;
    unsigned i;

    if ((s->lenght = get_file_size(filename)) == NULL) {
        strcpy(missed_file, filename);
        return NULL;
    }

    //s->lenght-=WAV_HEADER_SIZE;

    if ((s->buffer = (unsigned char*)malloc(s->lenght)) == NULL)
        return NULL;

    p = fopen(filename, "r+b");

    //fseek(p,WAV_HEADER_SIZE,SEEK_SET);
    fgets(s->buffer, s->lenght, p);

    fclose(p);

    num_of_loaded_sounds++;
    return 1;
}

void unload_sound(SOUND* s)
{
    free(s->buffer);
}

void unload_sounds(void)
{
    int i;

    for (i = 0; i < num_of_loaded_sounds; i++)
        unload_sound(&soundtab[i]);
}
