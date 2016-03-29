all: chip8 screen.o
screen.o: screen.c
	$(CC) $< -c -o $@
.PHONY: clean
clean:
	rm -rf chip8 *.o
