/*****************************************
  Mroczna Harmonia

  globals.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include "globals.h"

unsigned char keytab[256];

int zegar = 0;
int ile_aktywnych;
int bonus_typ;
char missed_file[256];

STATEK bonus;
STATEK statek[5];

POCISK pocisk[30];
SMUGA smuga[10];

KAPSULA kapsula;

POLE pole;
WYBUCH wybuch[MAX_BUM];

int b_punkt[30][60][2];

unsigned char sprite[MAX_SPRITES][400];
unsigned char spr_pocisk[MAX_MSPRITES][64];

unsigned char* bufor;
unsigned char *napis, *scroll_bufor;

SOUND soundtab[MAX_SOUNDS];
