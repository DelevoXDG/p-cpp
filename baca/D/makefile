CC=g++
CFLAGS=-std=c++17 -o
EXE = main
FILES = source.cpp
INC = include/
OUTDIR = build/

all: make run

clean:
	rm -rf $(EXE)

make: 
	@ $(CC) $(CFLAGS) $(EXE) $(FILES) 
run:
	@ ./$(EXE)
