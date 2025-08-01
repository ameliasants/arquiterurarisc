#include <stdint.h>
#ifndef CPU_H
#define CPU_H
#define STACK_MIN 0x1000
#define STACK_SIZE 0x1000
extern uint8_t stack_accessed[STACK_SIZE];
#define STACK_START 0x1000


#define NUM_REGS 16
#define STACK_MIN 0x1000

typedef struct {
    uint16_t regs[NUM_REGS]; // R0 a R15 (R14 = SP, R15 = PC)
    uint16_t IR;             // Instruction Register
    uint8_t Z;               // Zero flag
    uint8_t C;               // Carry flag
} Cpu;

void init_cpu(Cpu* cpu);
void print_state(Cpu* cpu);
void run(Cpu* cpu);
void print_accessed_stack(void);
void print_accessed_memory(void);
void init_stack_accessed(void);

#endif