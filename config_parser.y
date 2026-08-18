%{
	#include <stdio.h>
	#include <stdlib.h>

	#include "parser_types.h"
	t_parsConfig	parsConfig;
	t_parsStart		parsStart;
	t_parsClr		parsClr;
	t_parsClrRules	parsClrRules;
	t_oneClrRule	parsOneClrRule;

	void	yyerror (const char []);
	void	yy_warning (const char []);
	int		yylex (void);

# define YY_THROW(str)	{yyerror(str);YYABORT;}
%}

%union {
	uint64_t	uint64;
	uint8_t		uint8;
	char		*str;
	
	t_clr			clr;
	t_oneClrRules	oneClrRule;
	t_clrRules		clrRules;
}

%start config

%type <uint64>		uint64
%type <clr>			clr_rgb

%type <clr>			color
%type <clrRules>	clr_rules
%type <oneClrRule>	one_rule
%type <oneClrRule>	verbose_one_rule

%token UINT64 UINT8 STRING
%token CLR_RGB

%token SEPARATOR ASSIGN

%token WIDTH HEIGHT FNAME BACKGROUND FILL 

%token START N_START
%token COLOR RULES
%token X Y

%token TRED TGREEN TBLUE
%token MIN MAX DELTA

%%

config:	
	{
		parsConfig = (t_parsConfig){.nStart = 1};
	}
	settings {
		if (!parsConfig.width_Defined)	YY_THROW("Width not defined");
		if (!parsConfig.height_Defined)	YY_THROW("Height not defined");
		if (!parsConfig.width_Defined)	YY_THROW("Width not defined");
	}
	start_0_
	;

settings:
		separator_0_
	|	settings settings_content separator_1_
	;

settings_content:
		WIDTH ASSIGN uint64
		{
		if (parsConfig.width_Defined)	YY_THROW("Width redefined");
		if ($3 == 0)	{
			yy_warning("Width was 0, set to 1 instead");
			$3 = 1;
		}
		parsConfig.width_Defined = 1;
		parsConfig.width = $3;
	}
	|	HEIGHT ASSIGN uint64
	{
		if (parsConfig.height_Defined)	YY_THROW("Height redefined");
		if ($3 == 0)	{
			yy_warning("Height was 0, set to 1 instead");
			$3 = 1;
		}
		parsConfig.height_Defined = 1;
		parsConfig.height = $3;
	}
	|	N_START ASSIGN uint64
	{
		if (parsConfig.nStart_Defined)	YY_THROW("nStart redefined");
		if ($3 == 0)	{
			yy_warning("nStart was 0, set to 1 instead");
			$3 = 1;
		}
		parsConfig.nStart_Defined = 1;
		parsConfig.nStart = $3;
	}
	|	FNAME ASSIGN STRING
	{
		if (parsConfig.fName_Defined)	YY_THROW("Fname redefined");
		if (yylval.str == NULL)			YY_THROW("Fname malloc fail");
		parsConfig.fName_Defined = 1;
		parsConfig.fName = yylval.str;
	}
	|	backgroud	
	;
backgroud:
		BACKGROUND ASSIGN color
	{
		if (parsConfig.bg_Defined)	YY_THROW("BackGround redefined");
		parsConfig.bg_Defined = 1;
		parsConfig.bg = $3;
	}
	|	BACKGROUND ASSIGN FILL
	{
		if (parsConfig.bg_Defined)	YY_THROW("BackGround redefined");
		parsConfig.bg_Defined = 1;
		parsConfig.bgFill = 1;
	}
	;

start: 
	{parsStart = (t_parsStart){};}
		START '{' start_body '}'
	{
		//Dup start
	}
	;
start_body:
		separator_0_
	|	start_body start_body_content separator_1_
	;
 
start_body_content:
		X ASSIGN uint64
		{
			if (parsStart.x_Defined) YY_THROW("X redefined")
			parsStart.x_Defined = 1;
			parsStart.start.x = $3;
			printf("X = %lu\n ", $3);
		}
	|	Y ASSIGN uint64
		{
			if (parsStart.y_Defined) YY_THROW("Y redefined")
			parsStart.y_Defined = 1;
			parsStart.start.y = $3;
			printf("Y = %lu\n ", $3);
		}
	|	COLOR ASSIGN color
		{
			if (parsStart.clr_Defined) YY_THROW("Color redefined")
			parsStart.clr_Defined = 1;
			parsStart.start.baseClr = $3;
			printf("Clr = #%02X%02X%02X\n", $3.r, $3.g, $3.b);
		}
	|	RULES ASSIGN clr_rules
		{
			if (parsStart.rules_Defined) YY_THROW("Color rule redefined")
			parsStart.rules_Defined = 1;
			parsStart.start.rules = $3;
			printf("Color rule\n");
			printf("\t r: %u-%u (%u)\n", $3.r.min, $3.r.max, $3.r.delta);
			printf("\t g: %u-%u (%u)\n", $3.g.min, $3.g.max, $3.g.delta);
			printf("\t b: %u-%u (%u)\n", $3.b.min, $3.b.max, $3.b.delta);
		}
	;

color:
		CLR_RGB
		{	$$ = yylval.clr; }
	|	{parsClr = (t_parsClr){};}	'{' single_color ',' single_color ',' single_color '}'
		{	$$ = parsClr.clr;	}
	|	'{' uint64 ',' uint64 ',' uint64 '}'
		{	$$ = (t_clr){.r = $2, .g = $4, .b = $6}; }
	;

single_color:
		TRED ASSIGN uint64
		{	if (parsClr.r_Defined) YY_THROW("Red redefined")
			parsClr.clr.r = $3; parsClr.r_Defined = 1;
		} 
	|	TGREEN ASSIGN uint64
		{	if (parsClr.g_Defined) YY_THROW("Green redefined")
			parsClr.clr.g = $3; parsClr.g_Defined = 1;
		}
	|	TBLUE ASSIGN uint64
		{	if (parsClr.b_Defined)  YY_THROW("Blue redefined")
			parsClr.clr.b = $3; parsClr.b_Defined = 1;
		}
	;

clr_rules:
		{ parsClrRules = (t_parsClrRules){};}
		'{' separator_0_
			one_rule separator_1_
			one_rule separator_1_
			one_rule separator_0_
		'}'
		{ $$ = parsClrRules.rules; }
	|	clr_rgb '-' clr_rgb '(' uint64 ',' uint64 ',' uint64 ')'
	{
		t_clrRules	res = {};
		res.r = (t_oneClrRules){.min = $1.r, .max = $3.r, .delta = $5};
		res.g = (t_oneClrRules){.min = $1.g, .max = $3.g, .delta = $7};
		res.b = (t_oneClrRules){.min = $1.b, .max = $3.b, .delta = $9};
		$$ = res;
	}
	
	;

one_rule:
		TRED ASSIGN verbose_one_rule
		{
			if (parsClrRules.r_Defined)	YY_THROW("Color rule for red redefined");
			parsClrRules.r_Defined = 1;
			parsClrRules.rules.r = $3;
		}
	|	TGREEN ASSIGN verbose_one_rule
		{
			if (parsClrRules.g_Defined)	YY_THROW("Color rule for green redefined");
			parsClrRules.g_Defined = 1;
			parsClrRules.rules.g = $3;
		}
	|	TBLUE ASSIGN verbose_one_rule
		{
			if (parsClrRules.b_Defined)	YY_THROW("Color rule for blue redefined");
			parsClrRules.b_Defined = 1;
			parsClrRules.rules.b = $3;
		}
	;

verbose_one_rule:
		'{' uint64 ',' uint64 ',' uint64 '}'
		{
			t_oneClrRules	res = {};
			res.min = $2;
			res.max = $4;
			res.delta = $6;
			$$ = res;
		}
	|	'[' uint64 '-' uint64 ']' '(' uint64 ')'	// Sadly if i have [1-1] with the numbers and the - sticked together i get an error cause its a string
		{
			t_oneClrRules	res = {};
			res.min = $2;
			res.max = $4;
			res.delta = $7;
			$$ = res;
		}
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

uint64:	UINT64
	{ $$ = yylval.uint64; } ;

clr_rgb:	CLR_RGB
	{ $$ = yylval.clr; } ;


%%

t_parsStart	pStart = {};

void	yyerror (const char s[]) {
	fprintf (stderr, "\033[1;31mError: \033[0;31m%s\033[0m\n", s);
}

void	yy_warning (const char s[]) {
	fprintf (stderr, "\033[1;35mWarning: \033[0;35m%s\033[0m\n", s);
}

int main(void) {
	yyparse();
}
