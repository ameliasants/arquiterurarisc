#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    Cpu cpu;
    init_cpu(&cpu);
    init_stack_accessed();

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
    write_memory(0x8000, 0x1234);
    read_memory(0x8000);
    print_state(&cpu);
    print_accessed_stack();   
    print_accessed_memory(); 
    return 0;
}