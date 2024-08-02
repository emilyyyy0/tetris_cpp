CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2 -lSDL2_gfx -lSDL

TARGET = tetris
SOURCE = Pieces.cpp Board.cpp Game.cpp IO.cpp Main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean