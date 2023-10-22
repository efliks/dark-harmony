/*****************************************
  Mroczna Harmonia

  intro.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

void intro_animuj(void)
{
    int i, ile;
    
    for (ile = 0; ile < 20; ile++) {
        timer_start(3);

        for (i = 0; i < 21120; i += 20) {
            memcpy(bufor + i, napis + i, ile);
        }
    
        kopiuj_bufor();
        czysc_bufor();
        timer_wait();
    }
}

void przesun_scr_bufor(unsigned char* bufor)
{
    int i, j;
    unsigned char* ptr_buffer;

    for (i = 0; i < 8; i++) {
        ptr_buffer = bufor + 320 * i;
        for (j = 0; j < 319; j++, ptr_buffer++) {
            *ptr_buffer = *(ptr_buffer + 1);
        }
    }
}

void intro(void)
{
    int i, j, k, wspx, wspy, pom = 0, litera = 0;
    char str[5][30];
    char scroll_text[600], tmp[5];

    strcpy(str[0], "Version: 0.1");
    strcpy(str[1], "Code: Mfx");
    strcpy(str[2], "Gfx: Oolv");
    strcpy(str[3], "mikolaj.feliks@gmail.com");
    strcpy(str[4], "(C) 2001, 2023");

    strcpy(scroll_text, itoa(rekord[0].punkty, tmp, 10));
    strcat(scroll_text, " ");
    strcat(scroll_text, rekord[0].imie);
    strcat(scroll_text, " * ");
    for (i = 1; i < 12; i++) {
        strcat(scroll_text, itoa(rekord[i].punkty, tmp, 10));
        strcat(scroll_text, " ");
        strcat(scroll_text, rekord[i].imie);
        strcat(scroll_text, " * ");
    }

    memset(scroll_bufor, 0, 320 * 8);
    intro_animuj();
    for (j = 0; j < 30; j++) {
        timer_start(3);

        memcpy(bufor, napis, 21120);
        for (i = 0, wspx = 0; i < j; i++, wspx += 8) {
            for (k = 0, wspy = 76; k < 3; k++, wspy += 17) {
                if (j <= strlen(str[k]))
                    put_char(str[k][i], (160 - (j * 7 + j - 2) / 2) + wspx, wspy, bufor);
                else
                    put_string(str[k], centruj_x(str[k]), wspy, bufor);
            }
            if (j <= strlen(str[3]))
                put_char(str[3][i], (160 - (j * 7 + j - 2) / 2) + wspx, 168, bufor);
            else
                put_string(str[3], centruj_x(str[3]), 168, bufor);
            if (j <= strlen(str[4]))
                put_char(str[4][i], (160 - (j * 7 + j - 2) / 2) + wspx, 185, bufor);
            else
                put_string(str[4], centruj_x(str[4]), 185, bufor);
        }
        kopiuj_bufor();
        czysc_bufor();

        timer_wait();
    }

    play_sound(&soundtab[rand() % SND_EXPLOSION]);
    flash();

    while (1) {
        timer_start(3);

        memcpy(bufor, napis, 21120);
        put_string(str[0], centruj_x(str[0]), 76, bufor);
        put_string(str[1], centruj_x(str[1]), 93, bufor);
        put_string(str[2], centruj_x(str[2]), 110, bufor);

        put_string(str[3], centruj_x(str[3]), 168, bufor);
        put_string(str[4], centruj_x(str[4]), 185, bufor);
        if (!pom)
            put_char(scroll_text[litera], 311, 0, scroll_bufor);
        pom++;
        if (pom == 8) {
            pom = 0;
            litera++;
            if (scroll_text[litera] == NULL)
                litera = 0;
        }
        memcpy(bufor + 44480, scroll_bufor, 8 * 320);
        przesun_scr_bufor(scroll_bufor);

        kopiuj_bufor();
        czysc_bufor();

        timer_wait();

        if (keytab[KEY_SPACE])
            break;
        if (keytab[KEY_ESCAPE])
            koniec();
    }
}

void koniec(void)
{
    fade_down();
    zapisz_rekordy();

    clock_shutdown();
    restore_keyboard();

    sb_dsp_out(OFF_SPEAKER);
    disable_dma_int();

    unload_sounds();

    tryb_text();

    free(bufor);
    free(scroll_bufor);
    free(napis);

    exit(0);
}

int load_bin(unsigned char* where, char* filename)
{
    FILE* p;
    unsigned i = 0;

    if ((p = fopen(filename, "r+b")) == NULL) {
        strcpy(missed_file, filename);
        return NULL;
    }

    while (!feof(p)) {
        where[i] = fgetc(p);
        i++;
    }

    fclose(p);
    return 1;
}

int load_files(unsigned char* listfile, int flag)
{
    FILE* p;
    unsigned i, j, max_files;
    char txt_buffer[256], b;

    if ((p = fopen(listfile, "r")) == NULL) {
        strcpy(missed_file, listfile);
        return NULL;
    }

    if (flag == SPRITE_FILES)
        max_files = MAX_SPRITES;
    else if (flag == MSPRITE_FILES)
        max_files = MAX_MSPRITES;
    else
        max_files = MAX_SOUNDS;

    for (j = 0; j < max_files; j++) {
        i = 0;
        memset(txt_buffer, 0, 256);

        while (1) {
            b = fgetc(p);

            if (feof(p)) {
                fclose(p);
                strcpy(missed_file, listfile);
                strcat(missed_file, " - not enough defined files!");
                return NULL;
            }

            if (b == ';')
                break;

            txt_buffer[i] = b;
            i++;
        }

        switch (flag) {
        case SPRITE_FILES:
            if (!load_bin(sprite[j], txt_buffer)) {
                fclose(p);
                return NULL;
            }
            break;
        case MSPRITE_FILES:
            if (!load_bin(spr_pocisk[j], txt_buffer)) {
                fclose(p);
                return NULL;
            }
            break;
        case SOUND_FILES:
            if (!load_sound(&soundtab[j], txt_buffer)) {
                fclose(p);
                return NULL;
            }
        }
    }

    fclose(p);
    return 1;
}
