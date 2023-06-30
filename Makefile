CC=gcc
CFLAGS=-Wall
SOURCES=src/*.c

all:
	$(CC) $(CLFAGS) ${SOURCES} -o myld -lc -lgcc
