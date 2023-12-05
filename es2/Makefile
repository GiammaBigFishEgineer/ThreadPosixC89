# MakefileBanali

CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=
LIBRARIES=-lpthread

all: main.exe

main.exe: main.o
	gcc ${LFLAGS} -o main.exe main.o ${LIBRARIES}

main.o: main.c
	gcc -c ${CFLAGS} main.c

.PHONY:	clean

clean:
	rm -f main.exe main.o
