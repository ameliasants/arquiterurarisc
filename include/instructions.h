#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "cpu.h"
#include "io.h"

void execute_instruction(Cpu* cpu);
void update_flags(Cpu* cpu, uint16_t result, uint16_t a, uint16_t b, char op);

//  funções auxiliares
void executa_jmp(Cpu* cpu, int16_t offset);
void executa_jeq(Cpu* cpu, int16_t offset);
void executa_jne(Cpu* cpu, int16_t offset);
void executa_jlt(Cpu* cpu, int16_t offset);
void executa_jge(Cpu* cpu, int16_t offset);
void executa_and(Cpu* cpu, uint16_t instr);
void executa_shl(Cpu* cpu, uint16_t instr);
void executa_or(Cpu* cpu, uint16_t instr);
void executa_shr(Cpu* cpu, uint16_t instr);
void executa_jgt(Cpu* cpu, int16_t offset);
void executa_jle(Cpu* cpu, int16_t offset);
void executa_jnz(Cpu* cpu, int16_t offset);

#endif
