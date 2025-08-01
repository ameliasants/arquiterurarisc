#include "memory.h"
#include <stdint.h>  
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "cpu.h"
#include "utils.h"

#ifndef STACK_START
#define STACK_START 0x8000
#endif
#ifndef STACK_SIZE
#define STACK_SIZE 1024
#endif
extern uint8_t stack_accessed[STACK_SIZE];
uint16_t memory[MEM_SIZE];
uint8_t memory_accessed[MEM_SIZE] = {0};
uint8_t memory_read[MEM_SIZE] = {0}; 


void load_program(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir %s\n", filename);
        exit(1);
    }

    char line[32];
    uint16_t addr, instr;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%hx: 0x%hx", &addr, &instr) == 2) {
            memory[addr] = instr;
            memory_accessed[addr] = 1; 
            
        }
    }

    fclose(file);
}



uint16_t read_memory(uint16_t addr) {
    memory_read[addr] = 1;
     if (addr >= STACK_START && addr < STACK_START + STACK_SIZE) {
        stack_accessed[addr - STACK_START] = 1;
    }
   if (addr == CHAR_IN || addr == INT_IN) {
        uint16_t value = 0;
        handle_io(addr, &value, 0);
        return value;
    }

    return memory[addr];
}

void write_memory(uint16_t addr, uint16_t value) {
    memory[addr] = value;
    memory_accessed[addr] = 1;
   if (addr == CHAR_OUT || addr == INT_OUT) {
        handle_io(addr, &value, 1);
    }
}