%{
//#include <iostream>
#include <stdio.h>
//extern int yychar;

void yyerror(const char *msg)
{
    //std::cerr << msg  << " " << yylineno<< std::endl;
    //printf("yychar: %d\n", yychar);
    printf("ERROR %s\n", msg);
    // throw AVM::SyntaxError(yylineno, "LINE", "TOKEN");
}

%}

%token      ES_IMPLIES
%token      ES_MUTUAL_IMPLIES
%token      ES_OR
%token      ES_XOR
%token      ES_AND
%token      ES_NOT
%token      ES_FACT
%token      ES_SEPARATOR
%token      ES_COMMENT
%token      ES_OPEN_BRACKET
%token      ES_CLOSE_BRACKET

%left       ES_OR
%left       ES_XOR
%left       ES_AND
%left       ES_NOT

%%


IMPLIES:
                    EXPRESSION ES_IMPLIES EXPRESSION SEPARATORS
                    {
                        printf("IMPLIES EXPRESSION\n");
                    }

                    | EXPRESSION ES_MUTUAL_IMPLIES EXPRESSION SEPARATORS
                    {
                        printf("MUTUAL IMPLIES EXPRESSION\n");
                    }

SEPARATORS:
                    ES_SEPARATOR {printf("SEP\n");}
                    | ES_SEPARATOR SEPARATORS {printf("SEPS\n");}

EXPRESSION:
                    ES_FACT
                    {
                        printf("FACT\n");
                    }

                    | ES_NOT EXPRESSION
                    {
                        printf("UNARY NOT\n");
                    }

                    | EXPRESSION ES_OR EXPRESSION
                    {
                        printf("BOP OR\n");
                    }

                    | EXPRESSION ES_XOR EXPRESSION
                    {
                        printf("BOP XOR\n");
                    }

                    | EXPRESSION ES_AND EXPRESSION
                    {
                        printf("BOP AND\n");
                    }

                    | ES_OPEN_BRACKET EXPRESSION ES_CLOSE_BRACKET

%%
