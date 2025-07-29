CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj
TARGET = emulator.exe

# Lista EXPLÍCITA de arquivos fonte (evita problemas com wildcard)
SRC = $(SRC_DIR)/cpu.c $(SRC_DIR)/memory.c $(SRC_DIR)/instructions.c \
      $(SRC_DIR)/io.c $(SRC_DIR)/utils.c $(SRC_DIR)/main1.c
      
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
m
clean:
	@IF exist "*.out" del "*.out"  # para evitar acumular arquivos .out
	@if exist "$(OBJ_DIR)" rmdir /S /Q "$(OBJ_DIR)"
	@if exist "$(TARGET)" del "$(TARGET)"
	
rebuild: clean all	# garante que o executável seja recriado quando necessário

.PHONY: all clean
 
