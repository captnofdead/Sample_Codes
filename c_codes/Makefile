calculator:	calculator_0827.l calculator_0827.y main_0827.c
	lex calculator_0827.l
	yacc -d calculator_0827.y
	gcc -w main_0827.c lex.yy.c y.tab.c -o calc -lm
	./calc

