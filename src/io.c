#include "io.h"
#include <stdio.h>
#include <stdint.h>

// Define IO address constants
#define CHAR_IN  0x00
#define INT_IN   0x02
#define CHAR_OUT 0x04
#define INT_OUT  0x06

void handle_io(uint16_t addr, uint16_t* value, int is_write) {
    if (addr == CHAR_IN && !is_write) {
        *value = getchar();
    } else if (addr == INT_IN && !is_write) {
        scanf("%hu", value);
    } else if (addr == CHAR_OUT && is_write) {
        putchar(*value);
    } else if (addr == INT_OUT && is_write) {
        printf("%hu\n", *value);
    }
}