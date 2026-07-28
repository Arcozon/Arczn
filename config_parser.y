%{
	#include <stdio.h>
	#include <stdlib.h>

	// #include "types.h"
	// #include "arczn.h"
	// #include "color.h"

	#include "parser_types.h"
	// #include "config_parser.h"
	void	yyerror (const char[]);
	int  yylex (void);

	t_parsStart	pStart;
%}

%union {
	uint64_t	uint64val;
	uint8_t		uint8val;
	
	t_clr	clrval;
	t_oneClrRules	oneClrRuleval;
	t_clrRules		clrRuleval;
}

%start config

%token UINT64 UINT8

%token START N_START
%token SEPARATOR ASSIGN

%token TRED TGREEN TBLUE
%token MIN MAX DELTA

%%

config:
	/* start_0_ */
	start_0_
	;

start:
	START '{' start_body '}'
	{printf("start\n");}
	;
start_body:
	{printf("start Body\n");}
	;


red_rule:
	TRED rule 
green_rule:
	TGREEN rule 
blue_rule:
	TBLUE rule 

rule:
		'{' min max delta '}'
	|	compact_rule
	;

compact_rule:	'[' UINT8 '-' UINT8 ']' '(' UINT8 ')'
	;

min:
		MIN ':' UINT8 separator_1_
		{} //Return INT VAL
	|	{}//DEfault Val
	;


max:
		MAX ':' UINT8 separator_1_
		{} //Return INT VAL
	|	{}//DEfault Val
	;


delta:
		DELTA ':' UINT8 separator_1_
		{} //Return INT VAL 
	|	{}//DEfault Val
	;

n_start: 
	;

start_0_:
		separator_0_
	|	start_1_ separator_0_

start_1_: 
		start 
	|	start_1_ separator_1_ start
	;  

separator_0_:
	|	separator_1_;
separator_1_:
		SEPARATOR
	|	separator_1_ SEPARATOR
	;
%%

t_parsStart	pStart = {};

void	yyerror (const char s[]) {
	fprintf (stderr, "%s\n", s);
}

int main(void) {
	yyparse();
}
 