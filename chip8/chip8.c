#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t memory[4096]; /* memory */

uint16_t IP; /* PC */
uint8_t delay_timer; /* Delay timer */
uint8_t sound_timer; /* Sound timer */

uint8_t screen_surface[64 * 32]; /* 64 x 32 screen */

uint8_t sprites[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, /* 0 */
	0x20, 0x60, 0x20, 0x20, 0x70, /* 1 */
	0xF0, 0x10, 0xF0, 0x80, 0xF0, /* 2 */
	0xF0, 0x10, 0xF0, 0x10, 0xF0, /* 3 */
	0x90, 0x90, 0xF0, 0x10, 0x10, /* 4 */
	0xF0, 0x80, 0xF0, 0x10, 0xF0, /* 5 */
	0xF0, 0x80, 0xF0, 0x90, 0xF0, /* 6 */
	0xF0, 0x10, 0x20, 0x40, 0x40, /* 7 */
	0xF0, 0x90, 0xF0, 0x90, 0xF0, /* 8 */
	0xF0, 0x90, 0xF0, 0x10, 0xF0, /* 9 */
	0xF0, 0x90, 0xF0, 0x90, 0x90, /* A */
	0xE0, 0x90, 0xE0, 0x90, 0xE0, /* B */
	0xF0, 0x80, 0x80, 0x80, 0xF0, /* C */
	0xE0, 0x90, 0x90, 0x90, 0xE0, /* D */
	0xF0, 0x80, 0xF0, 0x80, 0xF0, /* E */
	0xF0, 0x80, 0xF0, 0x80, 0x80  /* F */
};

int main() {
	/* init */
	memcpy(memory, sprites, 80); /* copy sprites to memory */
	//printf("%s", sprites);
	//printf("%s", memory);

	int16_t opcode = 0x52E1; /* should be 16 bit long */

	switch(opcode & 0xF000) {
	case 0x0000: /* 0x0NNN */
		switch(opcode & 0xFF00) {
			case 0x0000: /* 0x00NN */
				switch(opcode) {
					case 0x00E0:
						printf("Clear screen\n");
						break;
					case 0x00EE:
						printf("Return from func\n");
						break;
					default:
						printf("Unknown 00%x\n", opcode);
						break;
				}
				break;
			default: /* 0x0NNN */
				printf("Call RCA 1802 at addr %x\n", opcode);
				break;
		}
		break;
	case 0x1000:
		printf("Jump to addr %x\n", opcode);
		break;
	case 0x2000:
		printf("Call subroutine at %x\n", opcode);
		break;
	case 0x3000:
		printf("Skip next instruction if V%x equals %x\n", 
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		break;
	case 0x4000:
		printf("Skip next instruction if V%x doesn't equal %x\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		break;
	case 0x5000:
		printf("Skips the next instruction if V%x equals V%x\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		break;
	case 0x6000:
		printf("Sets V%x to %x\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		break;
	case 0x7000:
		printf("Adds %x	to V%x\n",
			(opcode & 0x00FF), (opcode & 0x0F00) >> 8);
		break;

	default:
		printf("Other opcode\n");
		break;
	
	}		
	return 0;
}
