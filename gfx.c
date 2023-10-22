/*****************************************
  Mroczna Harmonia

  gfx.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <dos.h>
#include <string.h> // for memset

#include "globals.h"

unsigned char palette[768];


void tryb_graf()
{
    _AX = 0x13;
    geninterrupt(0x10);
}

void tryb_text()
{
    _AX = 0x3;
    geninterrupt(0x10);
}

void kopiuj_bufor()
{
    unsigned char far* ptr_vidmem = (unsigned char far *)0xA0000000L;
    memcpy(ptr_vidmem, bufor, 64000);
}

void czysc_bufor()
{
    unsigned char far* ptr_vidmem = (unsigned char far *)0xA0000000L;
    memset(bufor, 0, 64000);
}

void retrace()
{
    while (!(inportb(0x03da) & 8))
        ;
    while ((inportb(0x03da) & 8))
        ;
}

void set_palette(unsigned char* my_pal)
{
    int i;
        
    outportb(0x03c8, 0);
    
    for (i = 0; i < 768; i++) {
        outportb(0x03c9, my_pal[i]);
    }
}

void dump_palette(unsigned char* my_pal)
{
    int i;
        
    outportb(0x03c7, 0);
    
    for (i = 0; i < 768; i++) {
        my_pal[i] = inportb(0x03c9);
    }
}

// end of low-level code

void pasek(int x, int y, unsigned char kolor)
{
    int i;
    unsigned char* bptr = bufor + x + y * 320;

    for (i = 0; i < 8; i++, bptr++) {
        *bptr = kolor;
    }
}

void pixel(int x, int y, unsigned char color)
{
    if (x >= 0 && x <= 319 && y >= 0 && y <= 199) {
        *(bufor + x + y * 320) = color;
    }
}

void draw_sprite(unsigned char* sprite, int x, int y, int width, int height, unsigned char* where)
{
    int i, j;
    
    unsigned char* sprptr = sprite;
    unsigned char* bptr = where + x + y * 320;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++, sprptr++, bptr++) {
            if (*sprptr != 0) {
                *bptr = *sprptr;
            }
        }
        bptr += 320 - width;
    }
}

void save_pal(void)
{
    dump_palette(palette);
}

void renew_pal(void)
{
    set_palette(palette);
}

void paleta_inicjuj(void)
{
    int i;
    unsigned char my_pal[768], *ptr;

    dump_palette(my_pal);
    ptr = my_pal + 100 * 3;

    for (i = 0; i < 64; i++) {
        *(ptr++) = 0;
        *(ptr++) = 0;
        *(ptr++) = i;
    }
    for (i = 0; i < 64; i++) {
        *(ptr++) = i;
        *(ptr++) = 0;
        *(ptr++) = 0;
    }

    set_palette(my_pal);
}

void flash(void)
{
    int i, j;
    unsigned char my_pal[768], dest_pal[768], *srcp, *destp;

    dump_palette(dest_pal);

    memset(my_pal, 63, 768);
    set_palette(my_pal);

    for (i = 0; i < 64; i++) {
        srcp = my_pal;
        destp = dest_pal;

        for (j = 0; j < 768; j++) {
            if ((*srcp) > (*destp)) {
               (*srcp)--;
            }
            srcp++;
            destp++;
        }

        set_palette(my_pal);
        retrace();
    }
}

void fade_down(void)
{
    int i, j;
    unsigned char my_pal[768], *srcp;
    
    dump_palette(my_pal);

    for (j = 0; j < 64; j++) {
        
        srcp = my_pal;
        for (j = 0; j < 768; j++) {
            if ((*srcp) > 0) {
               (*srcp)--;
            }
            srcp++;
        }

        set_palette(my_pal);
        retrace();
    }
}
