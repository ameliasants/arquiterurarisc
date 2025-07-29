#include "cpu.h"
#include "memory.h"
#include "instructions.h"
#include <stdio.h>

void init_cpu(Cpu* cpu) {
    for (int i = 0; i < NUM_REGS; i++) cpu->regs[i] = 0;
    cpu->regs[14] = 0x8000; // SP
    cpu->Z = 0;
    cpu->C = 0;
}

void print_state(Cpu* cpu) {
    printf("\n===============================\n");
    printf("Registers:\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("R%d:\t0x%04X\n", i, cpu->regs[i]);
    }

    printf("\nFlags:\n");
    printf("Z = %d\n", cpu->Z);
    printf("C = %d\n", cpu->C);

    printf("\nStack:\n");
    printf("%04X:\t0x%04X\n", cpu->regs[14], memory[cpu->regs[14]]);

    printf("\nMemory:\n");
    printf("000A:\t0x%04X\n", memory[0x000A]);
}

void run(Cpu* cpu) {
    printf("PC inicial: %04X\n", cpu->regs[15]);
    while (1) {
        uint16_t instr = memory[cpu->regs[15]];
        printf("PC = %04X, Instr = %04X\n", cpu->regs[15], instr);

        execute_instruction(cpu);

        if (instr == 0xFFFF) break;
    }
}