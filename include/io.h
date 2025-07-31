#ifndef IO_H
#define IO_H
#include <stdint.h>

#define CHAR_IN  0xF000
#define INT_IN   0xF001
#define CHAR_OUT 0xF002
#define INT_OUT  0xF003

void handle_io(uint16_t addr, uint16_t* value, int is_write);

#endif