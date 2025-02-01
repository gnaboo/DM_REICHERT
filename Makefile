CC = gcc
CFLAGS = -Wall -Wvla -Wextra -fsanitize=address,undefined -g

# Default to all source directories if no specific directory is provided
SRC_DIR ?= .
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
EXECUTABLE = $(SRC_DIR)/main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

.PHONY: all clean
