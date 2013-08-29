CFLAGS = -g -Wall 
LIBS=-lncurses -lfl

SRCS=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SRCS))

CC=gcc

TARGET=bin/mazeofmenace

all: $(TARGET)

$(TARGET): parser  build $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

build:
	$(CC) $(CFLAGS) $(LIBS) -c -o $@

parser:
	lex src/*.l
	yacc -d src/*.y
	mv lex.yy.c y.tab.h y.tab.c src/

orm:
	rm $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET) 
