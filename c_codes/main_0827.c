#include<stdio.h>
int flag=0;

extern int yyparse();
extern int yylex();
int main()
{
	printf("---------------------------WELCOME TO THE CALCULATORR---------------------------\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("----------------------PLEASE READ THE RULES TO USE THE CALCULATOR----------------\n");
	printf("||                   Addition             ||                 +                  ||\n");
	printf("||                 Subtraction            ||                 -                  ||\n");
	printf("||               Multiplication           ||                 *                  ||\n");
	printf("||                   Division             ||                 /                  ||\n");
	printf("||                   Exponent             ||                 ^                  ||\n");
	printf("||                   Modulous             ||                 %%                  ||\n");
	printf("||             Logical Left Shift         ||                 <<                 ||\n");
	printf("||             Logical Right Shift        ||                 >>                 ||\n");
	printf("||           Arithematic Left Shift       ||                 <                  ||\n");
	printf("||           Arithematic Right Shift      ||                 >                  ||\n");
	printf("||           Brackets Open and Close      ||              '(',')'               ||\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("____________PLEASE NOTE THAT THE EXPRESSION SHOULD BE ENDED WITH A ';'___________\n");
	printf("MULTIPLE EXPRESSIONS CAN BE EVALUATED,FOR EXAMPLE 1+2;3+4; WILL GIVE RESULTS FOR BOTH\n");
	printf("PLEASE TRY TO USE BRACKETS APPROPRIATLY\n");   
	printf("PLEASE ENTER THE EXPRESSION - "); 
    	yyparse();
    	if(flag==0)
    	printf("\nTHE GIVEN EXPRESSION WAS CORRECT PLEASE VISIT AGAIN		\n");
    	return 0;
}

void yyerror()
{
    	printf("	THE GIVEN EXPRESSION WAS INCORRECT PLEASE ENTER THE VALID EXPRESSION ACCORDING TO RULES\n");
    	flag=1;
}
