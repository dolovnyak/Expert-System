yacc -d ESGrammar.yacc
lex ESLexer.lex
gcc main.c lex.yy.c y.tab.c
