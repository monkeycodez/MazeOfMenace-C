CFLAGS = -g -Wall -std=gnu11
LIBS= -lcurses -Iinclude

OBJDIR=obj

SRCS=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(addprefix $(OBJDIR)/, $(patsubst src/%.c,%.o,$(SRCS)))

CC=gcc

vpath %.c src

TARGET=bin/mazeofmenace

all: $(TARGET)

run: all
	$(TARGET)

$(TARGET):  build #parser
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

build:	$(OBJECTS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

parser:
	lex src/*.l
	yacc -d src/*.y
	mv lex.yy.c y.tab.h y.tab.c src/

orm:
	rm $(OBJECTS)

clean:
	rm $(OBJECTS) $(TARGET) 
