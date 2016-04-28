#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "instructions.h"
#include "tests.h"

proc pr;

void execInstruction(uint8_t opcode) {
	int i = (opcode & 0xF0) >> 6;
	void (*testCallback[3]) (uint8_t) = {ZZNNNNNN, mov, doC};
	testCallback[i](opcode);
}

void test_rcl() {
	pr.A = 0b11110010;
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	uint8_t opcode = 0b00000111;
	execInstruction(opcode);
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	assert(pr.A == 0b11100101 && (CF == 0x01));
}

void test_rrc() {
	pr.A = 0b11110010;
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	uint8_t opcode = 0b00001111;
	execInstruction(opcode);
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	assert(pr.A == 0b01111001 && (CF == 0x00));
}

void test_ral() {
	pr.A = 0b10110101;
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	uint8_t opcode = 0b00010111;
	execInstruction(opcode);
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	assert(pr.A == 0b01101010 && (CF == 0x01));
}

void test_rar() {
	pr.A = 0b01101010;
	pr.flags |= 0x01; /* CF = 1 */
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	uint8_t opcode = 0b00011111;
	execInstruction(opcode);
	DEBUG_PRINT(("A="binpat" CF=%d\n", tobin(pr.A), CF));
	assert(pr.A == 0b10110101 && (CF == 0x00));
}

void test_mov() {
	pr.C = 0b01101010;
	pr.flags |= 0x01; /* CF = 1 */
	DEBUG_PRINT(("A="binpat" C="binpat"\n", tobin(pr.A), tobin(pr.C)));
	uint8_t opcode = 0b01111001;
	execInstruction(opcode);
	DEBUG_PRINT(("A="binpat"\n", tobin(pr.A)));
	assert(pr.A == 0b01101010);
}

void test_movmem() {
	pr.C = 0b01101010;
	pr.H = 0x12;
	pr.L = 0x34;
	pr.flags |= 0x01; /* CF = 1 */
	DEBUG_PRINT(("M=%x [M]="binpat" C="binpat"\n", pr.HL, tobin(prM), tobin(pr.C)));
	uint8_t opcode = 0b01110001;
	execInstruction(opcode);
	DEBUG_PRINT(("[M]="binpat"\n", tobin(prM)));
	assert(prM == 0b01101010);
	opcode = 0b01000110;
	execInstruction(opcode);
	DEBUG_PRINT(("B="binpat"\n", tobin(pr.B)));
	assert(pr.B == 0b01101010);
}

int main() {
	int i;
	void (*tests[]) (void) = {test_rcl, test_rrc, test_ral, test_rar, test_mov, test_movmem};
	for(i = 0; i < 6; i++) {
		tests[i]();
		printf("\n");
	}
	return 0;
}
