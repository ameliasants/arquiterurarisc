#include "cpu.h"
#include "memory.h"
#include <stdio.h>

int main() {
    Cpu cpu;
    init_cpu(&cpu);
    load_program("programas/programa.txt");
    run(&cpu);
    print_state(&cpu);
    return 0;
}