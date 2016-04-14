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
	   NNN101 - DCR r/M
           000011 - INX B
	   100011 - INX D
	   000011 - INX H
	   001011 - DCX B
	   011011 - DCX D
	   101011 - DCX H
	   110001 - LXI SP
	   110011 - INX SP
	   111011 - DCX SP
	   000111 - RCL
	   001111 - RRC
	   010111 - RAL
	   011111 - RAR
	*/
}

void doC(uint8_t opcode) {
	printf("Hello c\n");
}
