#include "io.h"
#include <stdio.h>
#include <stdint.h>

#ifndef CHAR_IN
#define CHAR_IN 0x00
#endif
#ifndef INT_IN
#define INT_IN 0x02
#endif
#ifndef CHAR_OUT
#define CHAR_OUT 0x04
#endif
#ifndef INT_OUT
#define INT_OUT 0x06
#endif

void handle_io(uint16_t addr, uint16_t* value, int is_write) {
    if (!is_write) {
        if (addr == CHAR_IN) {
            printf("[CHAR IN] = ");
            *value = getchar();
        } else if (addr == INT_IN) {
            printf("[INT IN] = ");
            scanf("%hu", value);
        }
    } else {
        if (addr == CHAR_OUT) {
            printf("[CHAR OUT] = ");
            putchar((char)(*value & 0xFF));
            printf("\n");
        } else if (addr == INT_OUT) {
            printf("[INT OUT] = %hu\n", *value);
        }
    }
}