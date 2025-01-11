frontend: parser.tab.c lex.yy.c
	g++ parser.tab.c lex.yy.c -o frontend

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.h: parser.y
	bison -d parser.y

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm frontend parser.tab.c lex.yy.c parser.tab.h