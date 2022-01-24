%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
%}
%{
    int yylex();
    void yyerror();
%}


%union {
  double value;
  int val;
}

%token <value> NUMBER
%token <val> NUMS
%token RSL
%token LSL

%left RSL LSL
%left   '-' '+'
%left   '*' '/'
%left   '^' 
%left   '(' ')'


%type <value> InpuT Expression Term Factor shft
//%type <val> shft

%%

InpuT: 	  InpuT Expression ';' 			{printf("\n The answer to the next expression is =%f", $2);}
		| Expression ';' 				{printf("\n The answer is =%f", $1);}

Expression: 	  Expression '+' Term				{$$ = $1 + $3;}
    		| Expression '-' Term				{$$ = $1 - $3;}
    		| Term 					{$$ = $1;}
    
Term: 		  Term '*' Factor				{$$ = $1 * $3;}
		| Term '/' Factor 				{$$ = $1 / $3;}
		| Term LSL shft   				{$$ = (int) $1 << (int)$3;}
		| Term RSL shft   				{$$ = (int)$1 >> (int)$3;}
		| Term '<' Factor   				{$$ = (int)$1 << (int)$3;}
		| Term '>' Factor   				{int a=$1,b=$3,ans=-1;
								    for(int i=0;i<b;i++)
									 ans = ans ^ 1<<(31-i);
								    $$ = ans&(a>>b);}
		| Term '^' Factor   				{$$ = pow($1,$3);}
		| Term '%' Factor 				{$$ = (int)$1%(int)$3;}
		| Factor 					{$$=$1;}
Factor:  	NUMBER    					{$$ = $1;}
	        | shft 					{$$ = $1;}
	        | '-' Factor     				{$$ = -1 * $2;}
	        | '(' Expression ')' 				{$$ = $2;}    
shft: 		NUMS 						{$$ = $1;}
		| '(' Expression ')' 				{$$ = $2;};
/*shft: Expression '<' shft {$$ = $1<< $3;}
    |shft RSHIFT shft {$$ = $1 >> $3;}
    |shft LSHIFT shft {$$ = $1<< $3;}
    | NUMS {$$ = $1;};*/
%%





