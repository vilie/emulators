#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instructions.h"

proc pr;

void execInstruction(uint8_t opcode) {
	int i = (opcode & 0xF0) >> 6;
	void (*testCallback[3]) (uint8_t) = {doB, mov, doC};
	testCallback[i](opcode);
}

int main() {
	uint8_t opcode = 0x76;
	execInstruction(opcode);
	return 0;
}


