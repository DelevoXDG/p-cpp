CC=g++
CFLAGS=-std=c++11 -o
EXE = main
FILES = main.cpp
INC = include/
BUILD = bin

all: make run

clean:
	grep -r -I -L --exclude "*.*" . | xargs rm -f -v

make: 
	@ $(CC) $(CFLAGS) $(EXE) $(FILES) 
run:
	@ ./$(BUILD)/$(EXE)
