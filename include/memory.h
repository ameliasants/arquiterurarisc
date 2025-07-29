#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEM_SIZE 0x8000

// Declaração extern (diz ao compilador que a variável existe em outro lugar)
extern uint16_t memory[MEM_SIZE];

void load_program(const char* filename);
uint16_t read_memory(uint16_t addr);
void write_memory(uint16_t addr, uint16_t value);

#endif