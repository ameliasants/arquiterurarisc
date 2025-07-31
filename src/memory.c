#include "memory.h"
#include <stdint.h>  
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "cpu.h"

#ifndef MEM_SIZE
#define MEM_SIZE 65536  
#endif

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
            printf("Carregado: 0x%04X em 0x%04X\n", instr, addr);
        }
    }

    fclose(file);
}

#include <assert.h>

uint16_t read_memory(uint16_t addr) {
    // Se o endereço for o dispositivo de entrada de inteiros (INT_IN),
    // pedimos para o usuário digitar um valor e retornamos esse valor.
    if (addr == INT_IN) {
        uint16_t value;
        printf("[INT IN] = ");
        scanf("%hu", &value); // Lê um número inteiro sem sinal do usuário
        return value;         // Retorna o valor lido como se fosse o conteúdo da memória
    }

    // Caso contrário, retornamos normalmente o valor armazenado na memória
    return memory[addr];
}

void write_memory(uint16_t addr, uint16_t value) {
    memory[addr] = value;
    memory_accessed[addr] = 1;
    if (addr == CHAR_OUT || addr == INT_OUT) {
        handle_io(addr, &value, 1);
    }
}