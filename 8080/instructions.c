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

void ZZ(uint8_t opcode) {
	printf("TODO");
	/* last 3 */
	/* NNN110 - MVI r/M
	   [000/010/100]001 - LXI B, D, H
	   [001/011/101/111]001 - DAD B, D, H, SP
           [000/010/001/011/110/111/100/101]010 - STAX B/D; LDAX BD; STA; LDA
		SHLD, LHLD;
	   NNN100 - INR r/M
	   NNN101 - DEC r/M
           000111 - INC B & C
	   100011 - INC D & E
	   000011 - INC H & L
	   001011 - DEC B & C
	   011011 - DEC D & E
	   101011 - DEC H & L
	   110011 - INC SP
	   111011 - DCX SP

	*/
}

void doC(uint8_t opcode) {
	printf("Hello c\n");
}
