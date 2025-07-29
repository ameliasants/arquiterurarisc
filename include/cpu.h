#ifndef CPU_H
#define CPU_H
#define STACK_MIN 0x1000

#include <stdint.h>

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

#endif