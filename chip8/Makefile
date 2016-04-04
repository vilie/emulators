all: chip8
chip8: chip8.c screen_opengl.o
	$(CC) $^ -o $@ -lglut -lGL
screen_opengl.o: screen_opengl.c
	$(CC) $^ -c -o $@
screen_ncurses: screen_ncurses.c
	$(CC) $^ -o $@ -lncurses
.PHONY: clean
clean:
	rm -rf chip8 screen_ncurses screen_opengl.o
