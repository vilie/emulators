#include "instructions.h"
#include <stdio.h>

extern proc pr;

void mov(uint8_t opcode) {
	char reg[] = {'B', 'C', 'D', 'E', 'H', 'L', 'M', 'A'};
	if(((opcode >> 3) & 0x7) == 0x6 && (opcode & 0x7) == 0x6)
		hlt(opcode); /* mov M, M -> halt */
	else {
		DEBUG_PRINT(("mov %c %c\n", reg[(opcode >> 3) & 0x7], reg[opcode & 0x7]));
	}
}

void hlt(uint8_t opcode) {
	printf("halt\n");
}

void ZZNNNNNN(uint8_t opcode) {
	void (*rotates[4]) (uint8_t) = {rcl, rrc, ral, rar}; /* rotates */
	if((opcode & 0x07) == 0x07) /* ZZZNN111 */
		rotates[(opcode & 0x18) >> 3] (opcode);
	return;

	/* last 3 */
	/* NNN110 - MVI r/M
	   [000/010/100/110]001 - LXI B, D, H, SP
	   [001/011/101/111]001 - DAD B, D, H, SP
           [000/010/001/011/110/111/100/101]010 - STAX B/D; LDAX BD; STA; LDA
		SHLD, LHLD;
	   NNN100 - INR r/M
	   NNN101 - DCR r/M
           [000/010/100/110]011 - INX B, D, H, SP
	   [001/011/101/111]011 - DCX B, D, H, SP
	   000111 - RCL
	   001111 - RRC
	   010111 - RAL
	   011111 - RAR
	*/
}

void doC(uint8_t opcode) {}

void doB(uint8_t opcode) {}

void rcl(uint8_t opcode) {
	DEBUG_PRINT(("rcl\n"));
	pr.flags &= 0xFE;
	pr.flags += ((pr.A & 0x80) >> 7); /* CF set to most sign bit */
	pr.A = pr.A << 1 | pr.A >> 7; /* rotate left 1 */
}

void rrc(uint8_t opcode) {
	DEBUG_PRINT(("rrc\n"));
	pr.flags &= 0xFE;
	pr.flags += (pr.A & 0x01);
	pr.A = pr.A >> 1 | pr.A << 7; /* rotate right 1 */
}

void ral(uint8_t opcode) {
	DEBUG_PRINT(("ral\n  "));
	uint8_t backupFlags = pr.flags; /* blackup CF */
	rcl(opcode);
	DEBUG_PRINT(("  exchange CF with least significant in A\n"));
	pr.flags = (pr.flags & 0xFE) + (pr.A & 0x01); /* CF = least significant in A */
	pr.A = (pr.A & 0xFE) + (backupFlags & 0x01); /* A least significant = CF (backup) */
}

void rar(uint8_t opcode) {
	DEBUG_PRINT(("rar\n  "));
	uint8_t backupFlags = pr.flags; /* backup CF */
	rrc(opcode);
	DEBUG_PRINT(("  exchange CF with most significant in A\n"));
	pr.flags = (pr.flags & 0xFE) + (pr.A >> 7); /* CF = most significant in A */
	pr.A = (pr.A & 0x7F) + (backupFlags << 7); /* A most significant = CF (backup) */
}
