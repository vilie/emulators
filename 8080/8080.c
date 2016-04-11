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

void execInstruction(uint8_t opcode) {
	int i = (opcode & 0xF0) >> 6;
	void (*testCallback[3]) (uint8_t) = {doB, mov, doC};
	testCallback[i](opcode);
}

int main() {
	uint8_t opcode = 0x74;
	execInstruction(opcode);
	return 0;
}


