#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instructions.h"

proc pr;

void execInstruction(uint8_t opcode) {
	DEBUG_PRINT(("Processing %X\n", opcode)); 
	int i = (opcode & 0xF0) >> 6;
	void (*testCallback[3]) (uint8_t) = {ZZNNNNNN, mov, doC};
	testCallback[i](opcode);
}

int main() {
	pr.A = 0x3F;
	uint8_t opcode = 0x1F;
	execInstruction(opcode);
	return 0;
}


