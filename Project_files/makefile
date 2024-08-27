# Define the compiler
CC = gcc

# Define the target executable
TARGET = main

# Define the source files
SRCS = main.c Interface.c

# Define the header file directory
INCLUDE = -I.

# Define the object files (automatically derived from SRCS)
OBJS = $(SRCS:.c=.o)

# Compilation flags (no warning flags)
CFLAGS = -std=c11 $(INCLUDE)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
