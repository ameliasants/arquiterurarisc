#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEM_SIZE 65536

extern uint16_t memory[MEM_SIZE];
extern uint8_t memory_accessed[MEM_SIZE];
extern uint8_t memory_read[MEM_SIZE];  // <-- Adicione esta linha!


uint16_t read_memory(uint16_t addr);
void write_memory(uint16_t addr, uint16_t value);
void load_program(const char* filename);

#endif