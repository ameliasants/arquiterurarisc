#ifndef UTILS_H
#define UTILS_H

#include "cpu.h"

void stack_push(Cpu* cpu, uint16_t value);
uint16_t stack_pop(Cpu* cpu);

#endif