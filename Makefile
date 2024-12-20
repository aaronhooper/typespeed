CC=clang
CFLAGS=-Wall -Wextra -g
INCLUDES=-Iinclude
LIBS=-framework IOKit -framework Cocoa -Llib -lraylib

SRC_DIR=src
BUILD_DIR=build
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET=$(BUILD_DIR)/typespeed

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@
	cp -r assets $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf build *.dSYM .cache
