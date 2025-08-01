#ifndef MEMORY_H
#define MEMORY_H

#ifndef MEM_SIZE
#define MEM_SIZE 65536
#endif

#include <stdint.h>
extern uint16_t memory[MEM_SIZE];

uint16_t read_memory(uint16_t addr);
void write_memory(uint16_t addr, uint16_t value);
void load_program(const char* filename);

#endif