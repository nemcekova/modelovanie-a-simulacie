# Project: Implementácia simulácie plastov
# author Barbora Nemčeková xnemce06@stud.fit.vutbr.cz  Rene Bolf xbolfr00@stud.fit.vutbr.cz
# Debuf prepinač -g (v gdb bude vidno kod)

CC = g++
CFLAGS = -std=c++11
run:
	$(CC) $(CFLAGS) plasty.cpp -o plasty

clean:
	rm -rf plasty
	rm -rf plasty
