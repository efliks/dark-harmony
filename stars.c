/*****************************************
  Mroczna Harmonia

  stars.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <stdlib.h>

#include "globals.h"

typedef struct typGWIAZDA 
{
    int x;
    int y;
    int kolor;
    int v;
} GWIAZDA;

GWIAZDA gwiazda[50];
int licznik = 0;


void g_inicjuj(void)
{
    int i;
    GWIAZDA* g;

    for (i = 0; i < 50; i++) {
        g = &gwiazda[i];

        g->x = rand() % 320;
        g->y = rand() % 200;

        if (i < 10) {
            g->v = 0;
            g->kolor = 30;
        } else if (i >= 10 && i < 22) {
            g->v = 1;
            g->kolor = 27;
        } else {
            g->v = 2;
            g->kolor = 24;
        }
    }
}

void gwiazdy(void)
{
    int i, x, y;
    GWIAZDA* g;

    if ((++licznik) > 3) {
        licznik = 0;
    }

    for (i = 0; i < 50; i++) {
        g = &gwiazda[i];

        pixel(g->x, g->y, g->kolor);

        switch (g->v) {
        case 0:
            g->y++;
            break;
        case 1:
            if (licznik == 2 || licznik == 3)
                g->y++;
            break;
        case 2:
            if (licznik == 3)
                g->y++;
        }
        if (g->y > 199) {
            g->x = rand() % 320;
            g->y = 0;
        }
    }
}
