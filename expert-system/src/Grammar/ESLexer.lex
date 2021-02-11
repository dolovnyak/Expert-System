%{
#include "y.tab.h"
//int yylex();
%}

%%

[A-Z]           {printf("CHAR\n");return ES_FACT;}
"("             {return ES_OPEN_BRACKET;}
")"             {return ES_CLOSE_BRACKET;}
"+"             {return ES_AND;}
"|"             {return ES_OR;}
"^"             {return ES_XOR;}
"!"             {return ES_NOT;}
"=>"            {return ES_IMPLIES;}
"<=>"           {return ES_MUTUAL_IMPLIES;}
"\n"            {printf("NEW LINE\n");return ES_SEPARATOR;}

#[^\n]+[\n]     {;}
[\t\v\r\f ]+    {;}
.               {printf("error\n");}

%%

int yywrap (void)
{
    printf("finish input\n");
    return 1;
}
