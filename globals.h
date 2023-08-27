#ifndef _GLOBALS_H
#define _GLOBALS_H

#define KEY_SPACE 0x39
#define KEY_ESCAPE 0x01
#define KEY_UPARROW 0x48
#define KEY_DOWNARROW 0x50
#define KEY_LEFTARROW 0x4B
#define KEY_RIGHTARROW 0x4D
#define KEY_RIGHTCTRL 0x1D

#define DOWN 0
#define DOWN_FAST 1
#define DOWN_LEFT 2
#define DOWN_RIGHT 3
#define UP 4
#define UP_FAST 5
#define UP_LEFT 6
#define UP_RIGHT 7
#define SMUGA_N 0
#define SMUGA_T 1

#define BONUS_POLE 1
#define NOWA_GIW 2

#define JOB 0
#define ACID 2
#define BUZZ 4
#define RAIL 6
#define WEAK 8
#define C_LINE 10
#define SPAW 12
#define BALL 14

#define MAX_SPRITES 54
#define MAX_MSPRITES 16
#define MAX_SOUNDS 5
#define SPRITE_FILES 1
#define MSPRITE_FILES 2
#define SOUND_FILES 3

#define MAX_BUM 10

#define SND_EXPLOSION 3
#define SND_BONUS 3
#define SND_ROCKET 4

#define ON_SPEAKER 0x0d1
#define OFF_SPEAKER 0x0d3
#define SOUND_FREQUENCY 11025


typedef struct typSTATEK 
{
    int x, y;
    int kx, ky, zm_x, zm_y;
    int ruch;
    int v;
    int k, klatka[12];
    int aktywny;
    int giwera;
    int xs_min, xs_max;
    int poc_x[3];
    int licznik, pom1, pom2;
    int laser_pom;
} STATEK;

typedef struct typKAPSULA 
{
    int x;
    int y;
    int klatka;
    int aktywna;
    int giwera;
    int licznik, l2;
    int punkty;
    int pom, trafiona;
    int pom2;
} KAPSULA;

typedef struct typPOCISK 
{
    int x, y;
    int k1, k2;
    int zmiana_xy;
    int aktywny;
    int pom1, pom2, pom3;
} POCISK;

typedef struct typWYBUCH 
{
    int x;
    int y;
    int r;
    int kolor1, kolor2;
    int r_pom;
    int aktywny;
} WYBUCH;

typedef struct typPOLE 
{
    int aktywne;
    int pom;
    int vpom;
    int r;
    int kolor;
    int czas;
} POLE;

typedef struct typSMUGA 
{
    int x;
    int y[32];
    int aktywna;
    int typ;
    unsigned char kolor;
} SMUGA;

typedef struct typREKORD 
{
    int punkty;
    char imie[30];
} REKORD;

typedef struct tSOUND 
{
    unsigned char* buffer;
    unsigned lenght;
} SOUND;

// gfx.c
void tryb_graf(void);
void tryb_text(void);

void kopiuj_bufor(void);
void czysc_bufor(void);

void pixel(int x, int y, unsigned char kolor);
void draw_sprite(unsigned char* sprite, int x, int y, int width, int height);
void pasek(int x, int y, unsigned char kolor);

void renew_pal(void);
void save_pal(void);

void retrace(void);

void fade_down(void);
void flash(void);

// stars.c
void g_inicjuj(void);
void gwiazdy(void);

// player.c
void kaps_inicjuj(KAPSULA* kaps);
void kaps_wykonaj(KAPSULA* kaps);

// bullets.c
void smuga_nadaj0(void);
void smuga_inicjuj(int x, int y, int typ, unsigned char kolor);
void smuga_wykonaj(SMUGA* sm);

void p_inicjuj(int x, int y, int typ, int k, int zmiana_xy);
void p_nadaj0(void);
void p_kontrola_kaps(POCISK* poc, KAPSULA* kaps, POLE* ple);
void p_kontrola_stat(POCISK* poc, STATEK* sta, KAPSULA* kaps);

void poc_wykonaj(POCISK* poc);

// enemies.c
void stat_inicjuj(STATEK* sta, KAPSULA* kaps);
void stat_ruch(STATEK* sta);
void stat_ruch2(STATEK* statek);
void statek_wykonaj(STATEK* sta, int licznik);
void stat_wykonaj(void);
void stat_strzal(STATEK* sta, KAPSULA* kaps);

int stat_kstrl(STATEK* sta, KAPSULA* kaps);

// laser.c
void laser(int x, int y, KAPSULA* kaps, POLE* ple, int laser_pom);

// intro.c
void przesun_scr_bufor(unsigned char* bufor);

void intro(void);
void koniec(void);

void intro_animuj(void);
void paleta_inicjuj(void);

int load_bin(unsigned char* where, char* filename);
int load_files(unsigned char* listfile, int flag);

// boom.c
void w_inicjuj_sincos(void);
void w_nadaj0(void);
void w_wykonaj(WYBUCH* bum);
void w_inicjuj(int x0, int y0, unsigned char kolor1, unsigned char kolor2);

// font.c
void put_char(char ascii_code, int x, int y, unsigned char* where);
void put_string(char* text, int x, int y, unsigned char* where);
void init_font(void);

// bonus.c
void b_nadaj0(STATEK* bon);

void bonus_inicjuj(STATEK* bon);
void bonus_wykonaj(STATEK* bon, KAPSULA* kaps);

void pole_nadaj0(POLE* p);
void pole_inicjuj(POLE* p);
void pole_wykonaj(POLE* p, KAPSULA* kaps);

// results.c
int centruj_x(char* string);

void zapisz_rekordy(void);
void odczytaj_rekordy(void);
void zmien_rekordy(int punkty);

void drukuj_liste(void);
void brak_listy(void);

void analiza_wynikow(int punkty);

// control.c
void init_keyboard(void);
void restore_keyboard(void);

// clock.c
void timer_start(unsigned long ticks);
void timer_wait();

void clock_init(void);
void clock_shutdown(void);

// sounds.c
int sb_init(void);
void sb_dsp_out(unsigned char value);

void interrupt dma_int(void);

void enable_dma_int(void);
void disable_dma_int(void);

void set_freq(unsigned freq);
void set_dma(unsigned char page, unsigned off, unsigned lenght);

void play_sound(SOUND* s);

int load_sound(SOUND* s, char* filename);
void unload_sound(SOUND* s);

void unload_sounds(void);

unsigned get_file_size(char* filename);
void convert_address(unsigned segment, unsigned off1, unsigned char* page, unsigned* off2);


extern unsigned char keytab[256];

extern int ile_aktywnych;
extern int bonus_typ;
extern char missed_file[256];

extern STATEK bonus;
extern STATEK statek[5];

extern POCISK pocisk[30];
extern SMUGA smuga[10];

extern KAPSULA kapsula;

extern POLE pole;
extern WYBUCH wybuch[MAX_BUM];

extern REKORD rekord[12];

extern int b_punkt[30][60][2];

extern unsigned char sprite[MAX_SPRITES][400];
extern unsigned char spr_pocisk[MAX_MSPRITES][64];

extern unsigned char* bufor;
extern unsigned char *napis, *scroll_bufor;

extern SOUND soundtab[MAX_SOUNDS];

#endif // _GLOBALS_H
