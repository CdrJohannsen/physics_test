CC = g++
TARGET = main
LDLIBS=-lSDL2 -lSDL2_image
CFLAGS= -w

all: $(TARGET)
	make clear
	$(CC) -o $(TARGET) $(TARGET).cpp $(LDLIBS) $(CFLAGS)

run:
	make all
	./$(TARGET)

clear:
	rm -f $(TARGET)
