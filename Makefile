# Compiler and flags
CC := gcc
CFLAGS := -Wall -std=c11 `sdl2-config --cflags` -g 
LDFLAGS := `sdl2-config --libs` -lSDL2_image

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/project

# Find all .c source files in SRC_DIR recursively
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')

# Replace SRC_DIR with BUILD_DIR and .c with .o for object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(BIN)

# Link all object files into the binary
$(BIN): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files
clean:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)
	cp res $(BUILD_DIR) -r
# Convenience alias
run: all
	./$(BIN)

.PHONY: all clean run

