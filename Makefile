CC=clang
CFLAGS= -Wall -Werror -g
FRAMEWORKS=-framework IOKit -framework Cocoa
LIBS=

all: main.c
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(LIBS) -o main main.c libraylib.a

.PHONY: clean
clean:
	rm -rf main main.dSYM
