#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    Cpu cpu;
    init_cpu(&cpu);

    char filename[256] = "programas\\name.txt"; 
    if (argc > 1) {
        strncpy(filename, argv[1], sizeof(filename)-1);
        filename[sizeof(filename)-1] = '\0';
    } else {
        printf("Digite o nome do arquivo de programa  '%s': ", filename);
        char input[256];
        if (fgets(input, sizeof(input), stdin)) {
            input[strcspn(input, "\r\n")] = 0;
            if (input[0] != '\0') {
                strncpy(filename, input, sizeof(filename)-1);
                filename[sizeof(filename)-1] = '\0';
            }
        }
    }

    load_program(filename);

    run(&cpu);
    print_state(&cpu);
    print_memory_accesses();
    return 0;
}