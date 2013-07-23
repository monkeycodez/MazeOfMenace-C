CFLAGS=-g -Wall 
LIBS=-lncurses

SRCS=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SRCS))

CC=gcc

TARGET=bin/mazeofmenace

all: $(TARGET)

$(TARGET): build $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

build:
	$(CC) $(CFLAGS) $(LIBS) -c -o $@

orm:
	rm $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET)
