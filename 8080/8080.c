#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instructions.h"

struct proc {
	uint8_t A, flags;
	uint8_t B, C;
	uint8_t D, E;
	uint8_t H, L;
	uint16_t SP;
	uint16_t PC;
} pr;

void execInstruction(uint16_t opcode) {
	int i = (opcode & 0xF0) >> 4;
	void (*testCallback[3]) (void) = {doA, doB, doC};
	testCallback[i]();
}

int main() {
	uint8_t opcode = 0x24;
	execInstruction(opcode);
	return 0;
}


