%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(ExpertSystemData *expert_system_data, const char *msg)
{
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) + ", lookahead token number " + std::to_string(yychar));
}

%}

%union              {
                    char fact;
                    Expression* expression;
                    }
                    
%parse-param        {ExpertSystemData *expert_system_data}

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
%type<fact>         QUESTION_FACTS

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
                    | MAIN_EXPRESSION

SEPARATORS:
                    ES_SEPARATOR
                    | ES_SEPARATOR SEPARATORS

MAIN_EXPRESSION:
                    EXPRESSION ES_IMPLIES EXPRESSION
                    {
                        Expression *main_expression(new BinaryExpression($1, BinaryOperator::IMPLIES, $3));
                        expert_system_data->AddMainExpression(main_expression);
                    }
                    | EXPRESSION ES_MUTUAL_IMPLIES EXPRESSION
                    {
                        Expression *main_expression(new BinaryExpression($1, BinaryOperator::MUTUAL_IMPLIES, $3));
                        expert_system_data->AddMainExpression(main_expression);
                    }

EXPRESSION:
                    ES_FACT
                    {
                        Expression *expression(new FactExpression($1));
                        $$ = expert_system_data->Find(expression);
                        delete expression;
                    }
                    | ES_NOT EXPRESSION
                    {
                        Expression *expression(new UnaryExpression(UnaryOperator::NOT, $2));
                        if (expert_system_data->Find(expression) != nullptr)
                        {
                            $$ = expert_system_data->Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                    }
                    | EXPRESSION ES_OR EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::OR, $3));
                        if (expert_system_data->Find(expression) != nullptr)
                        {
                            $$ = expert_system_data->Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                    }
                    | EXPRESSION ES_XOR EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::XOR, $3));
                        if (expert_system_data->Find(expression) != nullptr)
                        {
                            $$ = expert_system_data->Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                    }
                    | EXPRESSION ES_AND EXPRESSION
                    {
                        Expression *expression(new BinaryExpression($1, BinaryOperator::AND, $3));
                        if (expert_system_data->Find(expression) != nullptr)
                        {
                            $$ = expert_system_data->Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                    }
                    | ES_OPEN_BRACKET EXPRESSION ES_CLOSE_BRACKET
                    {
                        Expression *expression(new UnaryExpression(UnaryOperator::PARENTHESES, $2));
                        if (expert_system_data->Find(expression) != nullptr)
                        {
                            $$ = expert_system_data->Find(expression);
                            delete expression;
                        }
                        else
                            $$ = expression;
                    }

SET_TRUE_FACTS:
                    ES_EQUALLY TRUE_FACTS
                    | ES_EQUALLY

TRUE_FACTS:
                    ES_FACT TRUE_FACTS
                    {
                        Expression *expression(new FactExpression($1));
                        expert_system_data->Find(expression)->UpdateState(Expression::State::True);
                        delete expression;
                        std::cout << "SET TRUE FACT " << $1 << std::endl;
                    }
                    | ES_FACT
                    {
                        Expression *expression(new FactExpression($1));
                        expert_system_data->Find(expression)->UpdateState(Expression::State::True);
                        delete expression;
                        $$ = $1;
                        std::cout << "SET TURE FACT " << $1 << std::endl;
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
                        $$ = $1;
                    }

%%
