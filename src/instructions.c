#include "instructions.h"
#include "cpu.h"
#include "memory.h"
#include "io.h"
#include "utils.h"
#include <stdio.h>
extern uint16_t memory[];

void update_flags(Cpu* cpu, uint16_t result, uint16_t a, uint16_t b, char op) {
    cpu->Z = (result == 0);

    switch(op) {
        case '+': 
            cpu->C = (result < a || result < b);
            break;
        case '-': 
            cpu->C = (a < b);
            break;
        case '&': 
        case '|': 
        case '^': 
            cpu->C = 0;
            break;
        case '<': // SHL
            cpu->C = (a & (1 << (16 - b))) != 0; 
            break;
        case '>': // SHR
            cpu->C = (a & (1 << (b - 1))) != 0;
            break;
        default:
            cpu->C = 0;
    }
}

void execute_instruction(Cpu* cpu) {
    uint16_t instr = read_memory(cpu->regs[15]);
    cpu->IR = instr;
    cpu->regs[15]++;

    uint8_t opcode = (instr >> 12) & 0xF; 

    switch (opcode) {
        case 0x0: {
            if (instr == 0x0000) {
                print_state(cpu); 
               // print_memory_accesses();
            }
            break;
        }

        case 0x1: {
            uint8_t tipo = (instr >> 9) & 0x7;
            int16_t offset = instr & 0x1FF;
            if (offset & 0x100) offset |= 0xFE00; 

            switch (tipo) {
                case 0: executa_jmp(cpu, offset); break;
                case 1: executa_jeq(cpu, offset); break;
                case 2: executa_jne(cpu, offset); break;
                case 3: executa_jlt(cpu, offset); break;
                case 4: executa_jge(cpu, offset); break;
                case 5: executa_jgt(cpu, offset); break;
                case 6: executa_jle(cpu, offset); break;
                case 7: executa_jnz(cpu, offset); break; 
                default: printf("Salto desconhecido: tipo %d\n", tipo); break;
            }
            break;
        }

       case 0x2: { // LDR Rd, [Rm]
            uint8_t rd = (instr >> 8) & 0xF;
            uint8_t rm = (instr >> 4) & 0xF;
            uint16_t addr = cpu->regs[rm];
            cpu->regs[rd] = read_memory(addr); 
            break;
        }
      case 0x3: { // STR Rn, [Rm]
            uint8_t rm = (instr >> 4) & 0xF; // Rm: base/endereçamento 
            uint8_t rn = instr & 0xF;        // Rn: valor a armazenar 
            uint16_t addr = cpu->regs[rm];
            uint16_t value = cpu->regs[rn];
            write_memory(addr, value);
            break;
        }
        case 0x4: {
            if (instr == 0x4000) {
                cpu->regs[15] = memory[cpu->regs[14]];
                cpu->regs[14]++;
            } else {
                uint8_t rd = (instr >> 8) & 0xF;
                uint8_t im = instr & 0xFF;
                cpu->regs[rd] = im;
            }
            break;
        }

       case 0x5: { // ADD Rd, Rm, Rn   --> Rd = Rm + Rn
            uint8_t rd = (instr >> 8) & 0xF;
            uint8_t rm = (instr >> 4) & 0xF;
            uint8_t rn = instr & 0xF;

            uint16_t result = cpu->regs[rm] + cpu->regs[rn];
            cpu->regs[rd] = result;

            update_flags(cpu, result, cpu->regs[rm], cpu->regs[rn], '+');
            break;
        }

        case 0x6: { // ADDI Rd, Rm, #Im   --> Rd = Rm + Im
            uint8_t rd = (instr >> 8) & 0xF;
            uint8_t rm = (instr >> 4) & 0xF;
            uint8_t im = instr & 0xF;

            uint16_t result = cpu->regs[rm] + im;
            cpu->regs[rd] = result;

            update_flags(cpu, result, cpu->regs[rm], im, '+');
            break;
        }

        case 0x7: { // SUB Rd, Rm, Rn   --> Rd = Rm - Rn
            uint8_t rd = (instr >> 8) & 0xF;
            uint8_t rm = (instr >> 4) & 0xF;
            uint8_t rn = instr & 0xF;

            uint16_t result = cpu->regs[rm] - cpu->regs[rn];
            cpu->regs[rd] = result;

            update_flags(cpu, result, cpu->regs[rm], cpu->regs[rn], '-');
            break;
        }

        case 0x8: { // SUBI Rd, Rm, #Im   --> Rd = Rm - Im
            uint8_t rd = (instr >> 8) & 0xF;
            uint8_t rm = (instr >> 4) & 0xF;
            uint8_t im = instr & 0xF;

            uint16_t result = cpu->regs[rm] - im;
            cpu->regs[rd] = result;

            update_flags(cpu, result, cpu->regs[rm], im, '-');
            break;
        }
        case 0x9: { // AND
            executa_and(cpu, instr);
            break;
        }
        case 0xA: { // OR
            executa_or(cpu, instr);
            break;
        }
        case 0xB: { // SHR
            executa_shr(cpu, instr);
            break;
        }
        case 0xC: { // SHL
            executa_shl(cpu, instr);
            break;
        }

        case 0xD: { // CMP Rm, Rn
            uint8_t rm = (instr >> 4) & 0xF;
            uint8_t rn = instr & 0xF;
            uint16_t a = cpu->regs[rm];
            uint16_t b = cpu->regs[rn];
            cpu->Z = (a == b);
            cpu->C = (a < b); 
            break;
        }

        case 0xE: { // PUSH Rn
            uint8_t rn = instr & 0xF;
            stack_push(cpu, cpu->regs[rn]);
            break;
        }

        case 0xF: {
            if (instr == 0xFFFF) {
    

            } else {
                uint8_t rd = (instr >> 8) & 0xF;
                cpu->regs[rd] = stack_pop(cpu);
            }
            break;
        }
        default:
            printf("Instrucao nao implementada: 0x%04X\n", instr);
            break;
    }
}

void executa_jmp(Cpu* cpu, int16_t offset) {
    cpu->regs[15] += offset;
    printf("JMP PC = 0x%04X\n", cpu->regs[15]);
}

void executa_jeq(Cpu* cpu, int16_t offset) {
    if (cpu->Z) {
        cpu->regs[15] += offset;
        printf("JEQ → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JEQ ignorado: Z = 0\n");
    }
}

void executa_jne(Cpu* cpu, int16_t offset) {
    if (!cpu->Z) {
        cpu->regs[15] += offset;
        printf("JNE → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JNE ignorado: Z = 1\n");
    }
}

void executa_jlt(Cpu* cpu, int16_t offset) {
    if (!cpu->Z && cpu->C) {
        cpu->regs[15] += offset;
        printf("JLT → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JLT ignorado: Z = %d, C = %d\n", cpu->Z, cpu->C);
    }
}

void executa_jge(Cpu* cpu, int16_t offset) {
    if (cpu->Z || !cpu->C) {
        cpu->regs[15] += offset;
        printf("JGE → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JGE ignorado: Z = %d, C = %d\n", cpu->Z, cpu->C);
    }
}

void executa_and(Cpu *cpu, uint16_t instr) {
    uint8_t rd = (instr >> 8) & 0xF;
    uint8_t rm = (instr >> 4) & 0xF;
    uint8_t rn = instr & 0xF;
    uint16_t result = cpu->regs[rm] & cpu->regs[rn];
    cpu->regs[rd] = result;
    update_flags(cpu, result, cpu->regs[rm], cpu->regs[rn], '&');
}

void executa_shl(Cpu *cpu, uint16_t instr) {
    uint8_t rd = (instr >> 8) & 0xF;
    uint8_t rm = (instr >> 4) & 0xF;
    uint8_t im = instr & 0xF;
    uint16_t result = cpu->regs[rm] << im;
    cpu->regs[rd] = result;
    update_flags(cpu, result, cpu->regs[rm], im, '<');
}
void executa_or(Cpu *cpu, uint16_t instr) {
    uint8_t rd = (instr >> 8) & 0xF;
    uint8_t rm = (instr >> 4) & 0xF;
    uint8_t rn = instr & 0xF;
    uint16_t result = cpu->regs[rm] | cpu->regs[rn];
    cpu->regs[rd] = result;
    update_flags(cpu, result, cpu->regs[rm], cpu->regs[rn], '|');
}
void executa_shr(Cpu *cpu, uint16_t instr) {
    uint8_t rd = (instr >> 8) & 0xF;
    uint8_t rm = (instr >> 4) & 0xF;
    uint8_t im = instr & 0xF;
    uint16_t result = cpu->regs[rm] >> im;
    cpu->regs[rd] = result;
    update_flags(cpu, result, cpu->regs[rm], im, '>');
}
void executa_jnz(Cpu* cpu, int16_t offset) {
    if (!cpu->Z) {
        cpu->regs[15] += offset;
        printf("JNZ → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JNZ ignorado: Z = 1\n");
    }
}
void executa_jgt(Cpu* cpu, int16_t offset) {
 
    if (!cpu->Z && !cpu->C) {
        cpu->regs[15] += offset;
        printf("JGT → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JGT ignorado: Z = %d, C = %d\n", cpu->Z, cpu->C);
    }
}
void executa_jle(Cpu* cpu, int16_t offset) {
   
    if (cpu->Z || cpu->C) {
        cpu->regs[15] += offset;
        printf("JLE → PC = 0x%04X\n", cpu->regs[15]);
    } else {
        printf("JLE ignorado: Z = %d, C = %d\n", cpu->Z, cpu->C);
    }
}