

all:
	lex *.l
	yacc -d *.y
	gcc *.c -o parse

clean:
	rm lex.yy.c y.tab.h y.tab.c parse
