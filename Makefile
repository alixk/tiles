CC=g++
CFLAGS=-c -Wall --std=gnu++0x
LDFLAGS=-lncurses

all: play

play: play.o game.o
	$(CC) play.o game.o $(LDFLAGS) -o play

play.o: game.o play.cpp
	$(CC) $(CFLAGS) play.cpp

game.o: game.h game.cpp
	$(CC) $(CFLAGS) game.cpp

clean:
	rm -rf *.o play
