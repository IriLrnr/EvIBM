# TODO: update gcc-9 version
CC = gcc-9
CFLAGS = -g -ansi -pedantic -Wall
LDFLAGS = -lgsl -lgslcblas -lm

TARGET_EXEC := EvIBM

BUILD_DIR := ./build
SRC_DIR := ./source

# Find all the C files in the source dir
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# String substitution for every C file
OBJS  := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./run.sh

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -I ./include $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: $(BUILD_DIR)
	rm -r $(BUILD_DIR)

doc:
	slip merge .source_doc.md > DOCUMENTATION.md
