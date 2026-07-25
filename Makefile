BUILD_DIR := build
SRC_DIR := src
CC := gcc

SRCS := command.c tokenizer.c
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/main.out: $(SRC_DIR)/main.c $(OBJS)
	$(CC) $^ -o $(BUILD_DIR)/main.out

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@

clean:
	rm -rf build
