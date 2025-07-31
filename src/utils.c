#include "utils.h"
#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef MEM_SIZE
#define MEM_SIZE 65536 
#endif

extern uint16_t memory[MEM_SIZE];

void stack_push(Cpu *cpu, uint16_t value) {
    cpu->regs[14]--; // SP--
    write_memory(cpu->regs[14], value);
}

uint16_t stack_pop(Cpu *cpu) {
    uint16_t value = read_memory(cpu->regs[14]);
    cpu->regs[14]++; 
    return value;
}