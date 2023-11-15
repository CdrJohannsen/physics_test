CC = g++
TARGET = main
OUTPUT = physics
LDLIBS=-lSDL2 -lSDL2_image
CFLAGS= -w

all:
	make clear
	$(CC) -o $(OUTPUT) $(TARGET).cpp $(LDLIBS) $(CFLAGS)

run:
	make all
	./$(OUTPUT)

clear:
	rm -f $(OUTPUT)
