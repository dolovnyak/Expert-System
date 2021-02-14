%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(const char *msg)
{
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) + ", lookahead token number " + std::to_string(yychar));
}

%}

%union              A{
                    char fact;
                    Expression* expression;
                    }

%token              ES_IMPLIES
%token              ES_MUTUAL_IMPLIES
%token              ES_OR
%token              ES_XOR
%token              ES_AND
%token              ES_NOT
%token              ES_SEPARATOR
%token              ES_COMMENT
%token              ES_OPEN_BRACKET
%token              ES_CLOSE_BRACKET
%token              ES_EQUALLY
%token              ES_QUESTION

%token<fact>        ES_FACT

%type<expression>   EXPRESSION
%type<fact>         TRUE_FACTS

%left               ES_OR ES_XOR
%left               ES_AND
%left               ES_NOT
%left               ES_SEPARATOR
%left               ES_FACT
%left               ES_EQUALLY ES_QUESTION

%%

LINES:
                    LINE
                    | LINE SEPARATORS LINES

LINE:
                    | SET_TRUE_FACTS {std::cout << "was inside SET_TRUE_FACTS" << std::endl << std::endl;}
                    | SET_QUESTION_FACTS {std::cout << "was inside SET_QUESTION_FACTS" << std::endl << std::endl;}
                    | MAIN_EXPRESSION {std::cout << std::endl;}

SEPARATORS:
                    ES_SEPARATOR
                    | ES_SEPARATOR SEPARATORS

MAIN_EXPRESSION:
                    EXPRESSION ES_IMPLIES EXPRESSION
                    {
                        Expression *main_expression(new BinaryExpression($1, BinaryOperator::IMPLIES, $3));
                        MainExpressionsList::Instance().AddMainExpression(main_expression);
                        std::cout << *main_expression << std::endl;
                    }
                    | EXPRESSION ES_MUTUAL_IMPLIES EXPRESSION
                    {
                        Expression *main_expression(new BinaryExpression($1, BinaryOperator::MUTUAL_IMPLIES, $3));
                        MainExpressionsList::Instance().AddMainExpression(main_expression);
                        std::cout << *main_expression << std::endl;
                    }

EXPRESSION:
                    ES_FACT
                    {
                        Expression *expression(new FactExpression($1));
                        if (MainExpressionsList::Instance().Find(expression) != nullptr)
                        {
                            $$ = MainExpressionsList::Instance().Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                        std::cout << *$$ << std::endl;
                    }
                    | ES_NOT EXPRESSION
                    {
                        Expression *expression(new UnaryExpression(UnaryOperator::NOT, $2));
                        if (MainExpressionsList::Instance().Find(expression) != nullptr)
                        {
                            $$ = MainExpressionsList::Instance().Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                        std::cout << *$$ << std::endl;
                    }
                    | EXPRESSION ES_OR EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::OR, $3));
                        if (MainExpressionsList::Instance().Find(expression) != nullptr)
                        {
                            $$ = MainExpressionsList::Instance().Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                        std::cout << *$$ << std::endl;
                    }
                    | EXPRESSION ES_XOR EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::XOR, $3));
                        if (MainExpressionsList::Instance().Find(expression) != nullptr)
                        {
                            $$ = MainExpressionsList::Instance().Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                        std::cout << *$$ << std::endl;
                    }
                    | EXPRESSION ES_AND EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::AND, $3));
                        if (MainExpressionsList::Instance().Find(expression) != nullptr)
                        {
                            $$ = MainExpressionsList::Instance().Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                        std::cout << *$$ << std::endl;
                    }
                    | ES_OPEN_BRACKET EXPRESSION ES_CLOSE_BRACKET
                    {
                        $$ = $2;
                    }

SET_TRUE_FACTS:
                    ES_EQUALLY TRUE_FACTS
                    | ES_EQUALLY

TRUE_FACTS:
                    ES_FACT TRUE_FACTS
                    {
                        std::cout << "SET TRUE FACT " << $1 << std::endl;
                    }
                    | ES_FACT
                    {
                        std::cout << "SET TURE FACT " << $1 << std::endl;
                        $$ = $1;
                    }

SET_QUESTION_FACTS:
                    ES_QUESTION QUESTION_FACTS
                    | ES_QUESTION

QUESTION_FACTS:
                    ES_FACT QUESTION_FACTS
                    {
                        std::cout << "SET QUESTION FACT " << $1 << std::endl;
                    }
                    | ES_FACT
                    {
                        std::cout << "SET QUESTION FACT " << $1 << std::endl;
                    }

%%
