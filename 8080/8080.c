#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void doA() {
	printf("Hello a\n");
}

void doB() {
	printf("Hello b\n");
}

void doC() {
	printf("Hello c\n");
}

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


