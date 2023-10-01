/*****************************************
  Mroczna Harmonia

  main.c   xxxxxxxxxxxx

  (C) 2001, 2023  M. Feliks
*****************************************/

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

void main(void)
{
    int i, licznik, pom = 0;
    char txt_bufor[4];
    KAPSULA* kaps = &kapsula;

    printf("Initializing sound...\n");

    if (!sb_init()) {
        printf("%s", "Cannot initialize sound card\n");
        exit(1);
    }

    printf("%s", "Allocating memory...\n");

    if ((bufor = (unsigned char*)malloc(64000)) == NULL || (scroll_bufor = (unsigned char*)malloc(320 * 66)) == NULL || (napis = (unsigned char*)malloc(21120)) == NULL) {
        free(bufor);
        free(scroll_bufor);
        printf("%s", "Not enough free memory!\n");
        exit(2);
    }

    printf("%s", "Loading files...\n");

    if (!load_files("sprites.dat", SPRITE_FILES) || !load_files("msprites.dat", MSPRITE_FILES) || !load_bin(napis, "gamedata\\intro.bin")) {
        printf("%s%s%s", "Unable to open file ", missed_file, "\n");
        free(bufor);
        free(scroll_bufor);
        free(napis);
        unload_sounds();
        exit(3);
    }

    odczytaj_rekordy();

    init_font();
    init_keyboard();
    clock_init();
    tryb_graf();
    paleta_inicjuj();
    save_pal();
    w_inicjuj_sincos();
    randomize();

    sb_dsp_out(ON_SPEAKER);
    enable_dma_int();
    set_freq(SOUND_FREQUENCY);

    while (1) {
        intro();

        kaps_inicjuj(kaps);
        p_nadaj0();
        w_nadaj0();
        b_nadaj0(&bonus);
        pole_nadaj0(&pole);
        smuga_nadaj0();
        g_inicjuj();

        ile_aktywnych = 0;
        bonus_typ = 0;
        licznik = 0;

        for (i = 0; i < 5; i++)
            stat_inicjuj(&statek[i], kaps);
        pom = 0;

        do {
            timer_start(1);

            gwiazdy();
            for (i = 0; i < 10; i++)
                smuga_wykonaj(&smuga[i]);
            bonus_wykonaj(&bonus, kaps);
            pole_wykonaj(&pole, kaps);
            stat_wykonaj();

            for (i = 0; i < 30; i++)
                poc_wykonaj(&pocisk[i]);
            for (i = 0; i < 10; i++)
                w_wykonaj(&wybuch[i]);
            kaps_wykonaj(kaps);

            put_string(itoa(kaps->punkty, txt_bufor, 10), 0, 0, bufor);
            put_string(itoa(kaps->giwera + 1, txt_bufor, 10), 312, 0, bufor);
            if (bonus_typ) {
                if ((licznik++) == 600) {
                    bonus_typ = 0;
                    licznik = 0;
                }
                if (bonus_typ == NOWA_GIW)
                    put_string("You've got a new weapon !", -1, 0, bufor);
                else if (bonus_typ == BONUS_POLE)
                    put_string("You've got a force field !", -1, 0, bufor);
            }
            if (pom < 100)
                pom++;

            if (keytab[KEY_SPACE] && !keytab[KEY_RIGHTCTRL] && !keytab[KEY_UPARROW] && !keytab[KEY_DOWNARROW] && !keytab[KEY_LEFTARROW] && !keytab[KEY_RIGHTARROW] && pom == 100) {
                put_string("Paused...", -1, 96, bufor);
                kopiuj_bufor();
                czysc_bufor();

                while (1) {
                    timer_start(1);

                    if (keytab[KEY_RIGHTCTRL] || keytab[KEY_UPARROW] || keytab[KEY_DOWNARROW] || keytab[KEY_LEFTARROW] || keytab[KEY_RIGHTARROW]) {
                        break;
                    }
                    timer_wait();
                }
            }

            kopiuj_bufor();
            czysc_bufor();

            timer_wait();

            if (keytab[KEY_ESCAPE])
                koniec();

        } while (kaps->aktywna);

        fade_down();
        renew_pal();
        analiza_wynikow(kaps->punkty);
    }
}
