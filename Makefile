CC  = cc
INP = AL-Share-File
OUT = *.c
ARG = -g -Wall -w
LIB = `pkg-config --libs --cflags gtk+-2.0`

all:
	$(CC) $(ARG) -o $(INP) $(OUT) $(LIB)
