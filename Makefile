CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = objs
BIN_DIR = bin
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/data.c $(SRC_DIR)/marketplace.c $(SRC_DIR)/utils.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = $(BIN_DIR)/marketplace

# Default target to build and run
all: $(EXEC)
	./$(EXEC)

# Rule to compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)         # Ensure the objs directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create the executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)         # Ensure the bin directory exists
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule to remove object files and the executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rule to run the program (can be invoked with `make run`)
run: $(EXEC)
	./$(EXEC)

# Optional rule for debugging with gdb
debug: $(SRC_FILES)
	$(CC) $(CFLAGS) -g -o $(EXEC) $(SRC_FILES)
	gdb $(EXEC)
