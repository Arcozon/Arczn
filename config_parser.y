%{
	#include <stdio.h>
	#include <stdlib.h>

	#include "arczn.h"
%}

%union {
	size_t	longval;
	
	t_clr	clrval;
	t_oneClrRules	oneClrRuleval;
	t_clrRules		clrRuleval;
}

%start config

%token INT

%token START_POINT N_POINT

%token TYPE TYPE_IVY TYPE_PETRI

%token RED GREEN BLUE
%token MIN MAX DELTA

%%

config:
	type 

type:
		TYPE ':'	gen_type
	;

gen_type:
	
color_rule:

blue_rule:
	BLUE rule 

rule:
		'{' min max delta '}'
	|	compact_rule
	;

compact_rule:	'[' INT '-' INT ']' '(' INT ')'
	;

min:
		MIN ':' INT ';'
		{} //Return INT VAL
	|	{}//DEfault Val
	;


max:
		MAX ':' INT ';'
		{} //Return INT VAL
	|	{}//DEfault Val
	;


delta:
		DELTA ':' INT ';'
		{} //Return INT VAL
	|	{}//DEfault Val
	;

%%

void	yyerror (const char s[]) {
	fprintf (stderr, "%s\n", s);
}

int main(void) {
	printf(".intel_syntax noprefix\n");
	yyparse();
}
