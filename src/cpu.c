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
    cpu->regs[14] = 0x8000; 
    cpu->Z = 0;
    cpu->C = 0;
    cpu->regs[10] = 0xF000; // R10: CHAR_IN
    cpu->regs[11] = 0xF001; // R11: INT_IN
    cpu->regs[12] = 0xF003; // R12: INT_OUT
    cpu->regs[13] = 0xF002; // R13: CHAR_OUT
}

void print_state(Cpu* cpu) {
    printf("\nRegisters:\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("R%d:\t0x%04X\n", i, cpu->regs[i]);
    }
    printf("\nFlags:\n");
    printf("Z = %d\n", cpu->Z);
    printf("C = %d\n", cpu->C);
    
}

void run(Cpu* cpu) {
    while (1) {
        uint16_t instr = memory[cpu->regs[15]];
        execute_instruction(cpu);
        if (instr == 0xFFFF) break;
    }
}

void print_accessed_memory(void) {
    printf("\nMemory (acessada):\n");
    for (uint32_t addr = 0; addr < MEM_SIZE; addr++) {
        if (memory_accessed[addr] || memory_read[addr]) {
            printf("%04X: 0x%04X\n", addr, memory[addr]);
        }
    }
}