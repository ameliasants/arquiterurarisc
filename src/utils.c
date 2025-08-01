#include "cpu.h"
#include "memory.h"
#include <stdio.h>

#ifndef STACK_START
#define STACK_START 0x8000
#endif
#ifndef STACK_SIZE
#define STACK_SIZE 1024
#endif
extern uint8_t stack_accessed[STACK_SIZE];
uint8_t stack_accessed[STACK_SIZE] = {0};


void init_stack_accessed(void) {
    for (int i = 0; i < STACK_SIZE; i++) stack_accessed[i] = 0;
}

void stack_push(Cpu *cpu, uint16_t value) {
    cpu->regs[14]--;
    write_memory(cpu->regs[14], value);
    if (cpu->regs[14] >= STACK_START && cpu->regs[14] < STACK_START + STACK_SIZE)
        stack_accessed[cpu->regs[14] - STACK_START] = 1;
}


uint16_t stack_pop(Cpu *cpu) {
    uint16_t value = read_memory(cpu->regs[14]);
    if (cpu->regs[14] >= STACK_START && cpu->regs[14] < STACK_START + STACK_SIZE)
        stack_accessed[cpu->regs[14] - STACK_START] = 1;
    cpu->regs[14]++;
    return value;
}

void print_accessed_stack(void) {
    printf("\nPILHA (acessada):\n");
    int found = 0;
    for (uint32_t i = 0; i < STACK_SIZE; i++) {
        if (stack_accessed[i]) {
            uint16_t addr = STACK_START + i;
            printf("%04X:\t0x%04X\n", addr, memory[addr]);
            found = 1;
        }
    }
    if (!found) printf("PILHA NAO ACESSADA)\n");
}

