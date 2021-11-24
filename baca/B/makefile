CC=g++
CFLAGS=-ftime-report -std=c++11 -o
EXE = main
FILES = main.cpp
INC = include/
OUTDIR = build/

all: make run

clean:
	rm -rf $(EXE)

make: 
	$(CC) $(CFLAGS) $(EXE) $(FILES) 
run:
	@ ./$(EXE)
