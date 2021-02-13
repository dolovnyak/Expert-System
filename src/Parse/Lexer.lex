%{
#include "Grammar.yy.hpp"
#include <iostream>

%}

%option nounput
%option noinput

%%

[A-Z]           {yylval.fact = yytext[0]; return ES_FACT;}

"("             {return ES_OPEN_BRACKET;}
")"             {return ES_CLOSE_BRACKET;}
"+"             {return ES_AND;}
"|"             {return ES_OR;}
"^"             {return ES_XOR;}
"!"             {return ES_NOT;}
"=>"            {return ES_IMPLIES;}
"<=>"           {return ES_MUTUAL_IMPLIES;}

"="[A-Z]+       {std::cout << yytext << std::endl;}
"?"[A-Z]+       {std::cout << yytext << std::endl;}

[\t\v\r\f ]+    {;}
#[^\n]+[\n]     {return ES_SEPARATOR;}
[\n]            {printf("NEW LINE\n");return ES_SEPARATOR;}
.               {std::cout << yytext << std::endl; throw std::runtime_error("LEX EXCEPTION: symbol doesn't correct");}

%%

int yywrap (void)
{
    std::cout << "finish input" << std::endl;
    return 1;
}
