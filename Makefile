CC=g++
-std=c++11 -lm

all: projekt

projekt: simpleca.o
	$(CC) $(CFLAGS) -o projekt simpleca.o

simpleca.o: simpleca.cpp
	$(CC) $(CFLAGS) -c simpleca.cpp

run: projekt
	./projekt

masks: projekt
	./projekt -m

distancing: projekt
	./projekt -d

masks_and_distancing: projekt
	./projekt -m -d

clean:
	rm -f projekt *.o


