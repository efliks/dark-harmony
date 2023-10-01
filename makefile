CC=c:\tc\bin\tcc.exe
LINK=c:\tc\bin\tlink.exe
CFLAGS=-G -a -ml -c

all: harmonia.exe

harmonia.exe: bonus.obj boom.obj bullets.obj clock.obj control.obj enemies.obj font.obj gfx.obj globals.obj intro.obj laser.obj main.obj player.obj results.obj sound.obj stars.obj
	$(LINK) @tlink.txt

bonus.obj: bonus.c
	$(CC) $(CFLAGS) bonus.c

boom.obj: boom.c
	$(CC) $(CFLAGS) boom.c

bullets.obj: bullets.c
	$(CC) $(CFLAGS) bullets.c

clock.obj: clock.c
	$(CC) $(CFLAGS) clock.c

control.obj: control.c
	$(CC) $(CFLAGS) control.c

enemies.obj: enemies.c
	$(CC) $(CFLAGS) enemies.c

font.obj: font.c
	$(CC) $(CFLAGS) font.c

gfx.obj: gfx.c
	$(CC) $(CFLAGS) gfx.c

globals.obj: globals.c
	$(CC) $(CFLAGS) globals.c

intro.obj: intro.c
	$(CC) $(CFLAGS) intro.c

laser.obj: laser.c
	$(CC) $(CFLAGS) laser.c

main.obj: main.c
	$(CC) $(CFLAGS) main.c

player.obj: player.c
	$(CC) $(CFLAGS) player.c

results.obj: results.c
	$(CC) $(CFLAGS) results.c

sound.obj: sound.c
	$(CC) $(CFLAGS) sound.c

stars.obj: stars.c
	$(CC) $(CFLAGS) stars.c

clean:
	del *.obj *.map harmonia.exe
