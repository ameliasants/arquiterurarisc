#include "io.h"
#include <stdio.h>
#include <stdint.h>

void handle_io(uint16_t addr, uint16_t* value, int is_write) {
    if (!is_write) {
        if (addr == CHAR_IN) {
            printf("[CHAR IN] = ");
            *value = getchar(); // lê um caractere
        } else if (addr == INT_IN) {
            printf("[INT IN] = ");
            scanf("%hu", value); // lê um inteiro
        }
    } else {
        if (addr == CHAR_OUT) {
            printf("[CHAR OUT] = ");
            putchar((char)(*value & 0xFF)); // imprime um caractere
            printf("\n");
        } else if (addr == INT_OUT) {
            printf("[INT OUT] = %hu\n", *value); // imprime um inteiro
        }
    }
}