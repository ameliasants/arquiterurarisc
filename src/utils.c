#include "utils.h"
#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void stack_push(Cpu* cpu, uint16_t value) {
    if (cpu->regs[14] <= STACK_MIN) {
        printf("Erro: Stack overflow (SP = %04X)\n", cpu->regs[14]);
        exit(1);
    }
    cpu->regs[14]--;
    memory[cpu->regs[14]] = value;
}

uint16_t stack_pop(Cpu* cpu) {
    if (cpu->regs[14] >= MEM_SIZE) {
        printf("Erro: Stack underflow\n");
        exit(1);
    }
    uint16_t value = memory[cpu->regs[14]];
    cpu->regs[14]++;
    return value;
}