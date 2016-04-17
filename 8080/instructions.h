#include <stdint.h>

typedef struct {
	uint8_t A, flags;
	union {
	uint8_t B, C;
	uint16_t BC;
	};
	union {
	uint8_t D, E;
	uint16_t DE;
	};
	union {
	uint8_t H, L;
	uint16_t HL;
	};
	uint16_t SP;
	uint16_t PC;
} proc ;

void mov(uint8_t opcode);

void doB(uint8_t opcode);

void doC(uint8_t opcode);

void hlt(uint8_t opcode);

void rcl(uint8_t opcode);

void rrc(uint8_t opcode);

void ral(uint8_t opcode);

void rar(uint8_t opcode); 
