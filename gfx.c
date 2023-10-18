/*****************************************
  Mroczna Harmonia

  gfx.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <dos.h>
#include <string.h> // for memset

#include "globals.h"

unsigned char paleta_r[256], paleta_g[256], paleta_b[256];


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
    while (!(inp(0x03da) & 8))
        ;
    while ((inp(0x03da) & 8))
        ;
}

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

void paleta_inicjuj(void)
{
    int i;

    outportb(0x03c8, 100);

    for (i = 0; i < 64; i++) {
        outportb(0x03c9, 0);
        outportb(0x03c9, 0);
        outportb(0x03c9, i);
    }
    for (i = 0; i < 64; i++) {
        outportb(0x03c9, i);
        outportb(0x03c9, 0);
        outportb(0x03c9, 0);
    }
}


void save_pal(void)
{
    int i;

    outp(0x03c7, 0);
    
    for (i = 0; i < 256; i++) {
        paleta_r[i] = inp(0x03c9);
        paleta_g[i] = inp(0x03c9);
        paleta_b[i] = inp(0x03c9);
    }
}

void renew_pal(void)
{
    int i;

    outp(0x03c8, 0);

    for (i = 0; i < 256; i++) {
        outp(0x03c9, paleta_r[i]);
        outp(0x03c9, paleta_g[i]);
        outp(0x03c9, paleta_b[i]);
    }
}

void flash(void)
{
    int i, j;
    unsigned char r, g, b;

    outp(0x03c8, 0);
    for (i = 0; i < 768; i++) {
        outp(0x03c9, 63);
    }

    for (i = 0; i < 64; i++) {
        for (j = 0; j < 256; j++) {
            outp(0x03c7, j);
            r = inp(0x03c9);
            g = inp(0x03c9);
            b = inp(0x03c9);

            if (r > paleta_r[j])
                r--;
            if (g > paleta_g[j])
                g--;
            if (b > paleta_b[j])
                b--;

            outp(0x03c8, j);
            outp(0x03c9, r);
            outp(0x03c9, g);
            outp(0x03c9, b);
        }

        retrace();
    }
}

void fade_down(void)
{
    int i, j;
    unsigned char r, g, b;

    for (j = 0; j < 64; j++) {
        for (i = 0; i < 256; i++) {
            outp(0x03c7, i);
            r = inp(0x03c9);
            g = inp(0x03c9);
            b = inp(0x03c9);

            if (r > 0)
                r--;
            if (g > 0)
                g--;
            if (b > 0)
                b--;

            outp(0x03c8, i);
            outp(0x03c9, r);
            outp(0x03c9, g);
            outp(0x03c9, b);
        }

        retrace();
    }
}
