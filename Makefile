CC=gcc
CFLAGS=-lWarn -pedantic

tempread: temperature.o 
	$(CC) temperature.o -L.  -lcurl -lwiringPi -o temperature


temperature.o:	temperature.c
	$(CC) $(CFLAGS) -c -ansi $<

all: temperature

clean:
	rm  temperature *.o
