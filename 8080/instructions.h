#include <stdint.h>

typedef struct {
	uint8_t A, flags;
	union {
	struct {uint8_t B, C;};
	uint16_t BC;
	};
	union {
	struct {uint8_t D, E;};
	uint16_t DE;
	};
	union {
	struct {uint8_t H, L;};
	uint16_t HL;
	};
	uint16_t SP;
	uint16_t PC;

	/* TODO: Maybe move the memory out of the struct? */
	uint8_t memory[65536];
} proc ;

#define prM (pr.memory[pr.HL])

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#define CF (pr.flags & 0x01)
#define PF (pr.flags & 0x04)
#define HC (pr.flags & 0x08)
#define IF (pr.flags & 0x0F)
#define ZF (pr.flags & 0x20)
#define SF (pr.flags & 0x40)

void mov(uint8_t opcode);

void ZZNNNNNN(uint8_t opcode);

void doB(uint8_t opcode);

void doC(uint8_t opcode);

void hlt(uint8_t opcode);

void rcl(uint8_t opcode);

void rrc(uint8_t opcode);

void ral(uint8_t opcode);

void rar(uint8_t opcode); 
