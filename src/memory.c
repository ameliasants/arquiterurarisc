#include "memory.h"
#include <stdint.h>  // Adicione esta linha para definir uint16_t
#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 65536  // Defina o tamanho da memória conforme necessário
// Definição real da variável (alocação de memória)
uint16_t memory[MEM_SIZE];  // Agora está correto

void load_program(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir %s\n", filename);
        exit(1);
    }

    char line[32];
    uint16_t addr, instr;

    while (fgets(line, sizeof(line), file)) {  // Corrigido {
        if (sscanf(line, "%hx: 0x%hx", &addr, &instr) == 2) {
            memory[addr] = instr;
            printf("Carregado: 0x%04X em 0x%04X\n", instr, addr);
        }
    }

    fclose(file);
}

uint16_t read_memory(uint16_t addr) {
    if (addr < MEM_SIZE) {
        return memory[addr];
    }
    return 0;
}

void write_memory(uint16_t addr, uint16_t value) {
    if (addr < MEM_SIZE) {
        memory[addr] = value;
    }
}