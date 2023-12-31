/*****************************************
  Mroczna Harmonia

  control.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <dos.h>
#include <string.h>

#include "globals.h"

void interrupt (*old_keyboard)(void);

void interrupt my_keyboard(void)
{
    int key;

    key = inportb(0x60);
    outportb(0x20, 0x20);

    if (key & 0x80) {
        keytab[key - 0x80] = 0;
    }
    else {
        keytab[key] = 1;
    }
}

void init_keyboard(void)
{
    old_keyboard = getvect(9);
    setvect(9, my_keyboard);
   
    memset(keytab, 0, 256);
}

void restore_keyboard(void)
{
    setvect(9, old_keyboard);
}
