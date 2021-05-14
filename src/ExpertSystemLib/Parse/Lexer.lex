%{
#include "Grammar.yy.hpp"
#include <iostream>

%}

%option nounput
%option noinput

%%

"="             {return ES_EQUALLY;}
"?"             {return ES_QUESTION;}
[A-Z]           {yylval.fact = yytext[0]; return ES_FACT;}
"("             {return ES_OPEN_BRACKET;}
")"             {return ES_CLOSE_BRACKET;}
"+"             {return ES_AND;}
"|"             {return ES_OR;}
"^"             {return ES_XOR;}
"!"             {return ES_NOT;}
"=>"            {return ES_IMPLIES;}
"<=>"           {return ES_MUTUAL_IMPLIES;}

[\t\v\r\f ]+    {;}
#[^\n]+[\n]     {return ES_SEPARATOR;}
[\n]            {return ES_SEPARATOR;}
.               {throw std::runtime_error("LEX EXCEPTION: lexeme \"" + std::string(yytext) + "\" doesn't correct");}

%%

int yywrap (void)
{
    return 1;
}