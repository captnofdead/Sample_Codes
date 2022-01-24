%{
    #include<stdio.h>
    #include "y.tab.h"
%}

%%

[ \t]        		;
[\n]        		return 0;
">>"        		return RSL;
"<<"        		return LSL;
[0-9]+"."[0-9]+ 	{yylval.value = atof(yytext); return NUMBER;}
[0-9]+          	{yylval.val = atoi(yytext); return NUMS;}
.           		return yytext[0];

%%

int yywrap()
{
    return 1;
}

