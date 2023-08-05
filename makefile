all: harmonia.exe

harmonia.exe: bonus.obj boom.obj bullets.obj clock.obj control.obj enemies.obj font.obj gfx.obj globals.obj intro.obj laser.obj main.obj player.obj results.obj sound.obj stars.obj
	tlink @tlink.txt

bonus.obj: bonus.c
	tcc -1 -ml -c bonus.c

boom.obj: boom.c
	tcc -1 -ml -c boom.c

bullets.obj: bullets.c
	tcc -1 -ml -c bullets.c

clock.obj: clock.c
	tcc -1 -ml -c clock.c

control.obj: control.c
	tcc -1 -ml -c control.c

enemies.obj: enemies.c
	tcc -1 -ml -c enemies.c

font.obj: font.c
	tcc -1 -ml -c font.c

gfx.obj: gfx.c
	tcc -1 -ml -c gfx.c

globals.obj: globals.c
	tcc -1 -ml -c globals.c

intro.obj: intro.c
	tcc -1 -ml -c intro.c

laser.obj: laser.c
	tcc -1 -ml -c laser.c

main.obj: main.c
	tcc -1 -ml -c main.c

player.obj: player.c
	tcc -1 -ml -c player.c

results.obj: results.c
	tcc -1 -ml -c results.c

sound.obj: sound.c
	tcc -1 -ml -c sound.c

stars.obj: stars.c
	tcc -1 -ml -c stars.c

clean:
	del *.obj *.map harmonia.exe
