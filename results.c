/*****************************************
  Mroczna Harmonia

  results.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "globals.h"

REKORD rekord[12];


int centruj_x(char* string)
{
    return 160 - (strlen(string) << 2);
}

void zapisz_rekordy(void)
{
    FILE* plik;
    int i, k;
    char txt_punkty[4], b;

    plik = fopen("list.dat", "w");

    for (i = 0; i < 12; i++) {
        itoa(rekord[i].punkty, txt_punkty, 10);

        for (k = 0; k < 4; k++) {
            b = txt_punkty[k];
            fputc(b, plik);
        }
        for (k = 0; k < 30; k++) {
            b = rekord[i].imie[k];
            fputc(b, plik);
        }
    }
    fclose(plik);
}

void odczytaj_rekordy(void)
{
    FILE* ptr;
    int i, nr_rekordu = 0;
    char txt_punkty[4], b;

    if ((ptr = fopen("list.dat", "r")) == NULL)
        brak_listy();
    else {
        while (!feof(ptr)) {
            for (i = 0; i < 4; i++) {
                b = fgetc(ptr);
                txt_punkty[i] = b;
            }
            rekord[nr_rekordu].punkty = atoi(txt_punkty);

            for (i = 0; i < 30; i++) {
                b = fgetc(ptr);
                rekord[nr_rekordu].imie[i] = b;
            }
            nr_rekordu++;
        }
        fclose(ptr);
    }
}

void zmien_rekordy(int punkty)
{
    int i, k, nr = -1;
    char imie[30], napis1[20], napis2[25], znak, txt_punkty[4];

    strcpy(napis1, "Summary: ");
    strcat(napis1, itoa(punkty, txt_punkty, 10));
    strcpy(napis2, "Type in your name");

    for (i = 0; i < 30; i++)
        imie[i] = 0;
    i = 0;
    restore_keyboard();
    while (1) {
        put_string(napis1, centruj_x(napis1), 73, bufor);
        put_string(napis2, centruj_x(napis2), 90, bufor);
        put_string(imie, centruj_x(imie), 107, bufor);

        kopiuj_bufor();
        czysc_bufor();

        znak = getch();
        if (znak == 13)
            break;
        else if (znak == 8) {
            for (i = 0; i < 30; i++)
                imie[i] = 0;
            i = 0;
        } else {
            if (i < 25)
                imie[i] = znak;
            i++;
        }
    }
    init_keyboard();
    for (i = 11; i > 0; i--) {
        if (punkty >= rekord[i].punkty && punkty < rekord[i - 1].punkty)
            nr = i;
    }
    if (punkty > rekord[0].punkty)
        nr = 0;
    if (nr >= 0) {
        for (i = 11; i > nr; i--) {
            rekord[i].punkty = rekord[i - 1].punkty;
            for (k = 0; k < 30; k++)
                rekord[i].imie[k] = rekord[i - 1].imie[k];
        }
        rekord[nr].punkty = punkty;
        strcpy(rekord[nr].imie, imie);
    }
}

void drukuj_liste(void)
{
    int i, y, ile_wierszy;
    char txt_punkty[4];
    
    for (ile_wierszy = 0; ile_wierszy < 12; ile_wierszy++) {
        timer_start(3);

        for (i = 0, y = 3; i <= ile_wierszy; i++, y += 17) {
            put_string(itoa(rekord[i].punkty, txt_punkty, 10), 30, y, bufor);
            put_string(rekord[i].imie, 70, y, bufor);
        }
    
        kopiuj_bufor();
        czysc_bufor();

        timer_wait();
    }
}

void analiza_wynikow(int punkty)
{
    if (punkty >= rekord[11].punkty)
        zmien_rekordy(punkty);
    drukuj_liste();

    play_sound(&soundtab[rand() % SND_EXPLOSION]);
    flash();

    while (1) {
        if (keytab[KEY_SPACE])
            break;
        if (keytab[KEY_ESCAPE])
            koniec();
    }
}

void brak_listy(void)
{
    int i, j;

    for (i = 0, j = 200; i < 12; i++, j -= 15) {
        rekord[i].punkty = j;
    }
    
    strcpy(rekord[0].imie, "Night Crawler");
    strcpy(rekord[1].imie, "Rapid Fire");
    strcpy(rekord[2].imie, "Grinder");
    strcpy(rekord[3].imie, "Electric Eye");
    strcpy(rekord[4].imie, "Devil's Child");
    strcpy(rekord[5].imie, "Jawbreaker");
    strcpy(rekord[6].imie, "The Sentinel");
    strcpy(rekord[7].imie, "Turbo Lover");
    strcpy(rekord[8].imie, "Johnny B. Goode");
    strcpy(rekord[9].imie, "Leather Rebel");
    strcpy(rekord[10].imie, "Demonizer");
    strcpy(rekord[11].imie, "Spectre");
}
