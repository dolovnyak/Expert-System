%{
#include <iostream>
#include "Grammar.yy.hpp"

extern int yychar;
extern int yylex();

void yyerror(ExpertSystemData *expert_system_data, const char *msg)
{
    (void)expert_system_data;
    throw std::runtime_error("YACC EXCEPTION: " + std::string(msg) + ", lookahead token number " + std::to_string(yychar));
}

%}

%union              {
                    char fact;
                    Expression *expression;
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
                        expert_system_data->AddMainExpression(
                            expert_system_data->Find(new BinaryExpression($1, BinaryOperator::IMPLIES, $3)));
                    }
                    | EXPRESSION ES_MUTUAL_IMPLIES EXPRESSION
                    {
                        expert_system_data->AddMainExpression(
                            expert_system_data->Find(new BinaryExpression($1, BinaryOperator::MUTUAL_IMPLIES, $3)));
                    }

EXPRESSION:
                    ES_FACT
                    {
                        $$ = expert_system_data->Find(new FactExpression($1));
                    }
                    | ES_NOT EXPRESSION
                    {
                        $$ = expert_system_data->Find(new UnaryExpression(UnaryOperator::NOT, $2));
                    }
                    | EXPRESSION ES_OR EXPRESSION
                    {
                        $$ = expert_system_data->Find(new BinaryExpression($1, BinaryOperator::OR, $3));
                    }
                    | EXPRESSION ES_XOR EXPRESSION
                    {
                        $$ = expert_system_data->Find(new BinaryExpression($1, BinaryOperator::XOR, $3));
                    }
                    | EXPRESSION ES_AND EXPRESSION
                    {
                        $$ = expert_system_data->Find(new BinaryExpression($1, BinaryOperator::AND, $3));
                    }
                    | ES_OPEN_BRACKET EXPRESSION ES_CLOSE_BRACKET
                    {
                        $$ = expert_system_data->Find(new UnaryExpression(UnaryOperator::PARENTHESES, $2));
                    }

SET_TRUE_FACTS:
                    ES_EQUALLY TRUE_FACTS
                    | ES_EQUALLY

TRUE_FACTS:
                    ES_FACT TRUE_FACTS
                    {
                        expert_system_data->Find(new FactExpression($1))->UpdateState(Expression::State::True);
                        std::cout << "SET TRUE FACT " << $1 << std::endl;
                    }
                    | ES_FACT
                    {
                        expert_system_data->Find(new FactExpression($1))->UpdateState(Expression::State::True);
                        $$ = $1;
                        std::cout << "SET TURE FACT " << $1 << std::endl;
                    }

SET_QUESTION_FACTS:
                    ES_QUESTION QUESTION_FACTS
                    | ES_QUESTION

QUESTION_FACTS:
                    ES_FACT QUESTION_FACTS
                    {
                        expert_system_data->AddQueryExpression(expert_system_data->Find(new FactExpression($1)));
                        std::cout << "SET QUESTION FACT " << $1 << std::endl;
                    }
                    | ES_FACT
                    {
                        expert_system_data->AddQueryExpression(expert_system_data->Find(new FactExpression($1)));
                        $$ = $1;
                        std::cout << "SET QUESTION FACT " << $1 << std::endl;
                    }

%%
