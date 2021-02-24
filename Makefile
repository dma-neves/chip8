LIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

_DEPS=main.c Chip8.h Display.h Emulator.h Buzzer.h
DEPS=$(patsubst %,src/%,$(_DEPS))

CC=gcc
CFLAGS=-I src

ODIR=obj
_OBJ=main.o Chip8.o Display.o Emulator.o Buzzer.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

chip8.out: $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(ODIR)/*.o chip8.out

