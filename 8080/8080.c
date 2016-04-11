#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instructions.h"

void execInstruction(uint16_t opcode) {
	int i = (opcode & 0xF000) >> 12;
	void (*testCallback[3]) (void) = {doA, doB, doC};
	testCallback[i]();
}

int main() {
	uint16_t opcode = 0x1234;
	execInstruction(opcode);
	return 0;
}


