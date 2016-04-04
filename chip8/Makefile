all: chip8 screen_ncurses
chip8: chip8.c screen_opengl.c
	$(CC) $? -o $@ -lglut -lGL
screen_ncurses: screen_ncurses.c
	$(CC) $< -o $@ -lncurses
.PHONY: clean
clean:
	rm -rf chip8 screen_ncurses screen_opengl
