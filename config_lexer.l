%{
	#include <stdio.h>
	#include <stdlib.h>

	// #include "types.h"
	// #include "arczn.h"
	// #include "color.h"
	#include "parser_types.h"

	#include "config_parser.h"
	#include <ctype.h>
%}

%%

"start"		{DEBUG("Start");	return (START);	}
"nStart"	{	return (N_START);	}

"red"	{	return (TRED);	}
"green"	{	return (TGREEN);	}
"blue"	{	return (TBLUE);	}

"min"	{	return (MIN);	}
"max"	{	return (MAX);	}
"delta"	{	return (DELTA);	}

[\n;]		{ DEBUG("Separator");  return (SEPARATOR); }
[:=]		{ return (ASSIGN); }

[0-9]+	{	yylval.uint64val = strtol(yytext, NULL, 10);		return(UINT64);	}

[0-9a-fA-F]{2}										{yylval.uint8val =  strtol(yytext, NULL, 16);	return(UINT8); }
^(([0-1]?[0-9]?[0-9])|([2][0-4][0-9])|(25[0-5]))$	{yylval.uint8val =  strtol(yytext, NULL, 10);	return(UINT8); }

"#"		{ return ('#'); }
"-"		{ return ('-'); }
"["		{ return ('['); }
"]"		{ return (']'); }
"{"		{ return ('{'); }
"}"		{ return ('}'); }

[ \t]+  {}

%%
 
int yywrap(void) { return 1; }
 