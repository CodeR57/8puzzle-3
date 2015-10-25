#Makefile for 8puzzle

comp := g++

all: bin 8puzzle

bin:
	[ ! -d $bin ] && mkdir bin

8puzzle: bin
	$(comp) ./src/main.cpp -o ./bin/8puzzle

clean:
	rm -rf bin
