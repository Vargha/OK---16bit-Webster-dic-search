
CFLAGS=-std=c99 -Wall -pedantic

ok: ok.o
	gcc ok.o -o ok

ok.o: ok.c
	gcc -c $(CFLAGS) ok.c

clean:
		rm ok *.o
