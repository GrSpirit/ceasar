CC=cc
DEBUG=-g
STANDARD=-std=c99
CFLAGS=-Wall $(STANDARD) $(DEBUG)
OBJ=main.o ceasar.o utf8.o config.o

all: ceasar

ceasar: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

#%.o: %.c %.h %.cpp %.hpp $(DEPS)
.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o ceasar
