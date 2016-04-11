#include "instructions.h"
#include <stdio.h>

void mov(uint8_t opcode) {
	char reg[] = {'B', 'C', 'D', 'E', 'H', 'L', 'M', 'A'};
	if(((opcode >> 3) & 0x7) == 0x6 && (opcode & 0x7) == 0x6)
		hlt(opcode); /* mov M, M -> halt */
	else {
		printf("mov %c %c\n", reg[(opcode >> 3) & 0x7], reg[opcode & 0x7]);
	}
}

void hlt(uint8_t opcode) {
	printf("halt\n");
}

void doB(uint8_t opcode) {
	printf("Hello b\n");
}

void doC(uint8_t opcode) {
	printf("Hello c\n");
}
