# Define source files
SRC = $(wildcard *.c)

# Define binary name (e.g. main)
BIN = main

# Compiler flags
CFLAGS += -Werror -Wall -Wextra -g
# CFLAGS += --std=c99

# The 'all' target builds the project
all: $(BIN)

# Build the binary from the source files
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

# The 'run' target runs the compiled binary after building
run: $(BIN)
	./$(BIN)

# Clean the build artifacts
clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~

# Format the code using indent
indent:
	indent -linux -i4 -nut -ts2 *.c

.PHONY: all clean run indent
