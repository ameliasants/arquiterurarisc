#include "cpu.h"
#include "memory.h"
#include "instructions.h"
#include <stdio.h>

#ifndef MEM_SIZE
#define MEM_SIZE 65536
#endif
extern uint8_t memory_accessed[];
extern uint8_t memory_read[];
extern uint16_t memory[];

void init_cpu(Cpu* cpu) {
    for (int i = 0; i < NUM_REGS; i++) cpu->regs[i] = 0;
    cpu->regs[14] = 0x8000; // SP
    cpu->Z = 0;
    cpu->C = 0;
}

void print_state(Cpu* cpu) {
    printf("\nRegisters:\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("R%d:\t0x%04X\n", i, cpu->regs[i]);
    }
    printf("\nFlags:\n");
    printf("Z = %d\n", cpu->Z);
    printf("C = %d\n", cpu->C);
    
    printf("\nStack:\n");
    printf("%04X:\t0x%04X\n", cpu->regs[14], memory[cpu->regs[14]]);
    
}

// Não imprime mais nada no final
void run(Cpu* cpu) {
    while (1) {
        uint16_t instr = memory[cpu->regs[15]];
        execute_instruction(cpu);
        if (instr == 0xFFFF) break;
    }
}

void print_memory_accesses(void) {
    extern uint16_t memory[];
    extern uint8_t memory_accessed[];
    extern uint8_t memory_read[];
    printf("\n Memory:\n");
    for (uint32_t addr = 0; addr < MEM_SIZE; addr++) {
        if (memory_accessed[addr]) {
            printf(" %04X: 0x%04X\n", (uint16_t)addr, memory[addr]);
        }
        if (memory_read[addr]) {
            printf(" %04X: 0x%04X\n", (uint16_t)addr, memory[addr]);
        }
    }
}