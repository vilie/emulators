/*
 * Author: Valentin Ilie
 * Contact: <valentin.ilie@gmail.com>
 * License: GNU General Public License (GPL) v3
 * Copyright (C) 2016 Valentin Ilie
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t memory[4096]; /* memory */

uint16_t IP; /* PC */
uint16_t I; /* 16 bit register */
uint8_t SP; /* Stack pointer */
uint8_t V[16]; /* V registers */
uint16_t stack[16]; /* stack registers */
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

	int16_t opcode = 0xFA55; /* should be 16 bit long */

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
						printf("Unknown 00%X\n", opcode);
						break;
				}
				break;
			default: /* 0x0NNN */
				printf("Call RCA 1802 at addr %X\n", opcode);
				break;
		}
		break;
	case 0x1000:
		printf("Jump to addr %X\n", opcode);
		opcode = opcode & 0x0FFF;
		break;
	case 0x2000:
		printf("Call subroutine at %X\n", opcode);
		stack[SP++] = opcode;
		opcode = opcode & 0x0FFF;
		break;
	case 0x3000:
		printf("Skip next instruction if V%X equals %X\n", 
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		if(V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			opcode = opcode + 2;
		opcode = opcode + 2;
		break;
	case 0x4000:
		printf("Skip next instruction if V%X doesn't equal %X\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		if(V[(opcode & 0x0F00) >> 8] != (opcode & 0x0FF))
			opcode = opcode + 2;
		opcode = opcode + 2;
		break;
	case 0x5000:
		printf("Skips the next instruction if V%X equals V%X\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		if(V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F) >> 4])
			opcode = opcode + 2;
		opcode = opcode + 2;
		break;
	case 0x6000:
		printf("Sets V%X to %X\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
		opcode = opcode + 2;
		break;
	case 0x7000:
		printf("Adds %X	to V%X\n",
			(opcode & 0x00FF), (opcode & 0x0F00) >> 8);
		V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
		opcode = opcode + 2;
		break;
	case 0x8000:
		switch(opcode & 0x000F) {
		case 0x0000:
			printf("Sets V%X to V%X\n", 
				(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0001:
			printf("Sets V%X to V%X or V%X\n",
				(opcode & 0x0F00) >> 8, (opcode & 0x0F00) >> 8,
				(opcode & 0x00F0) >> 4);
			V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0002:
			printf("Sets V%X to V%X and V%X\n",
				(opcode & 0x0F00) >> 8, (opcode & 0x0F00) >> 8,
				(opcode & 0x00F0) >> 4);
			V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0003:
			printf("Sets V%X to V%X xor V%X\n",
				(opcode & 0x0F00) >> 8, (opcode & 0x0F00) >> 8,
				(opcode & 0x00F0) >> 4);
			V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0004:
			printf("Add V%X to V%X. VF set to 1 when carry.\n",
				(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			if(V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 4]))
				V[0xF] = 1;
			else
				V[0xF] = 0;
			V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0005:
			printf("V%X is substracted from V%X. VF is set to 0 wh"
				"en there is a borrow, and 1 when there isn't\n",
				(opcode & 0x00F0) >> 4, (opcode & 0x0F00) >> 8);
			
			if(V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0)])
				V[0xF] = 1;
			else
				V[0xF] = 0;
			V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
			opcode = opcode + 2;
			break;
		case 0x0006:
			printf("Shifts V%X right by one. VF is set to the "
				"value of the least significant bit of the V%X "
				"before the shift\n", (opcode & 0x0F00) >> 8,
				(opcode & 0x0F00) >> 8);
			V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x0001;
			V[(opcode & 0x0F00) >> 8] >>= 1;
			opcode = opcode + 2;
			break;
		case 0x0007:
			printf("Sets V%X to V%X minus V%X. VF is set to 0 when "
				"there's a borrow, and 1 when there isn't\n",
				(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, 
				(opcode & 0x0F00) >> 8);
			if(V[(opcode & 0x00F0) >> 4] < V[(opcode & 0x0F00) >> 8])
				V[0xF] = 0;
			else
				V[0xF] = 1;
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4]-\
				V[(opcode & 0x0F00) >> 8];
			opcode = opcode + 2;
			break;
		case 0x000E:
			printf("Sets V%X left by one. VF is set to the value "
				"of the most significant bit of V%X before the "
				"shift\n", (opcode & 0x0F00) >> 8,
				(opcode & 0x0F00) >> 8);
			V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7 ;
			V[(opcode & 0x0F00) >> 8] <<= 1;
			opcode = opcode + 2;
			break;
		default:
			printf("Unknows opcode %X\n", opcode);
		}
		break;
	case 0x9000:
		printf("Skips the next instruction if V%X doesn't equal to V%X\n",
			(opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			if(V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
				opcode = opcode + 4;
			else
				opcode = opcode + 2;
			break;
	case 0xA000:
		printf("Sets I to address %X\n", opcode & 0x0FFF);
			I = opcode & 0x0FFF;
			opcode = opcode + 2;
			break;
	case 0xB000:
		printf("Jumps to the address %X plus V0\n",
			(opcode & 0x0FFF));
			opcode = (opcode & 0x0FFF) + V[0x0];
			break;
	case 0xC000:
		printf("Sets V%X to the result of a bitwise and operation on "
			"a random number and %X\n", (opcode & 0x0F00) >> 8,
			(opcode & 0x00ff));
			V[(opcode & 0x0F00) >> 8] = 0x42 && (opcode & 0x00FF);
			opcode = opcode + 2;
			break;
	case 0xD000: /* 0xDXYN */
		printf("Sprites stored in memory at location in the index "
			"register (L), 8 bits wide. Wraps around the screen "
			"If when draws, clears a pixel, register VF is set to "
			"1 otherwise it is zero. All drawing is XOR drawing "
			"(i.e. it toggles the screen pixels). Sprites are "
			"drawn at starting position V%X, V%X. %X is the number"
			" of 8bit rows that need to be drawn. If N is greater "
			"than 1, second line continues at position VX, VY+1, "
			"and so on.", (opcode & 0x0F00) >> 8, 
			(opcode & 0x00F0) >> 4, (opcode & 0x000F));
			break;
	case 0xE000:
		switch(opcode & 0x000F) {
		case 0x000E:
			printf("Skips the next instruction if the key stored "
				"in V%X is pressed \n", (opcode & 0x0F00) >> 8);
			break;
		case 0x0001:
			printf("Skips the next instruction if the key stored "
				"in V%X isn't pressed \n",
				(opcode & 0x0F00) >> 8);
			break;
		default:
			printf("Unknown opcode %hX\n", opcode);
			break;
		}
		break;
	case 0xF000:
		switch (opcode & 0x000F) {
		case 0x0007:
			printf("Sets V%X to the value of the delay timer\n",
				(opcode & 0x0F00) >> 8);
			V[(opcode & 0x0F00) >> 8] = delay_timer;
			opcode = opcode + 2;
			break;
		case 0x000A:
			printf("A key press is awaited, and then stored in "
				"V%X \n", (opcode & 0x0F00) >> 8);
			break;
		case 0x0008:
			printf("Sets the sound timer to V%X\n",
				(opcode & 0x0F00) >> 8);
			sound_timer = V[(opcode & 0x0F00) >> 8];
			opcode = opcode + 2;
			break;
		case 0x000E:
			printf("Adds V%X to I\n", (opcode & 0x0F00) >> 8);
			I = I + V[(opcode & 0x0F00) >> 8];
			opcode = opcode + 2;
			break;
		case 0x0009:
			printf("Sets L to the location of the sprite for the "
				"character in V%X. Characters 0-F (in hexadeci"
				"mal) are represented by a 4x5 font.\n",
				(opcode & 0x0F00) >> 8);
			break;
		case 0x0003:
			printf("Stores the Binary-coded decimal representation"
				" of V%X, with the most significant three "
				"digits at the address in L, the middle digit "
				"at L plus 1, and the least significant digit "
				"at L plus 2. \n", (opcode & 0x0F00) >> 8);
			break;
		case 0x0005:
			switch (opcode & 0x00F0) {
			case 0x0050:
				printf("Stores V0 to V%X in memory starting "
					"at address L\n",
					(opcode & 0x0F00) >> 8);
				break;
			case 0x0060:
				printf("Fills V0 to V%X with values from "
					"memory starting at address L\n",
					(opcode & 0x0F00) >> 8);
				break;
			case 0x0010:
				printf("Sets the delay timer to V%X\n", 
				(opcode & 0x0F00) >> 8);
				delay_timer = V[(opcode & 0x0F00) >> 8];
				opcode = opcode + 2;
				break;
			default:
				printf("Unknown opcode %hX\n", opcode);
				break;
			}
			break;
		default:
			printf("Unknown opcode %hX\n", opcode);
			break;
		}
		break;
 
	default:
		printf("Other opcode\n");
		break;
	
	}		
	return 0;
}
