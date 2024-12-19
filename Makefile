CC=clang
CFLAGS=-Wall -Wextra -g
FRAMEWORKS=-framework IOKit -framework Cocoa
LIBS=libraylib.a

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(LIBS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET) main.dSYM

.PHONY: all clean
