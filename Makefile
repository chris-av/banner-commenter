CC := gcc
CFLAGS := -Wall -Wextra -std=c99


SRC_DIR := .
BIN_DIR := bin
OBJ_DIR := objs

# source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# object files
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# executable
BIN := $(BIN_DIR)/banner-commenter

# main target
all: $(BIN)

version.h:
	bash get_version.sh


# linking binary
$(BIN): $(OBJS) version.h | $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# compiling object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) version.h
	$(CC) $(CFLAGS) -c $< -o $@


# create the folders if they don't exist
$(OBJ_DIR): 
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@



clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) version.h


.PHONY: clean

