CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lSDL2 -lSDL2_gfx -lSDL

TARGET = sdl_test
SOURCE = sdl_test.cpp Pieces.cpp Board.cpp Game.cpp IO.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean