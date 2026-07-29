%{
	#include <stdio.h>
	#include <stdlib.h>

	// #include "types.h"
	// #include "arczn.h"
	// #include "color.h"
	#include "parser_types.h"

	#include "config_parser.h"
	#include <ctype.h>

	t_clr	strToClr(const char *);
	char	*dupAddDotPng(const char *);
%}

%%

width|w		{	return (WIDTH);	}
height|h	{	return (HEIGHT);}
file|fname	{	return (FNAME);}

"start"		{	return (START);	}
"nStart"	{	return (N_START);	}

[xX]		{	return(X);	}
[yY]		{	return(Y);	}


rule|rules	{	return (RULES);	}
color|clr	{	return (COLOR);	}
red|r		{	return (TRED);	}
green|g		{	return (TGREEN);}
blue|b		{	return (TBLUE);	}

"min"	{	return (MIN);	}
"max"	{	return (MAX);	}
"delta"	{	return (DELTA);	}

[\n;]		{  return (SEPARATOR); }
[:=]		{ return (ASSIGN); }

[0-9]+	{	yylval.uint64 = strtol(yytext, NULL, 10);		return(UINT64);	}

[0-9a-fA-F]{2}		{yylval.uint64 = strtol(yytext, NULL, 16);	return(UINT64); }
x[0-9a-fA-F]{2}		{yylval.uint64 = strtol(yytext + 1, NULL, 16);	return(UINT64); }
0x[0-9a-fA-F]{2}	{yylval.uint64 = strtol(yytext + 2, NULL, 16);	return(UINT64); }

#[0-9a-fA-F]{6}		{yylval.clr = strToClr(yytext);	return(CLR_RGB); }


"#"		{ return ('#'); }
","		{ return (','); }
"-"		{ return ('-'); }
"["		{ return ('['); }
"]"		{ return (']'); }
"("		{ return ('('); }
")"		{ return (')'); }
"{"		{ return ('{'); }
"}"		{ return ('}'); }

[0-9a-zA-Z_\.\-]+	{yylval.str = dupAddDotPng(yytext);	DEBUG("str");return(STRING); }

[ \t]+  {}
\/\/.*	{}; // Simple line comment

. 		{fprintf(stderr, "Unknown char: %.1s[%d]\n", yytext, yytext[0]);}

%%

uint8_t	charHexToUInt8(char c) {
	if (isdigit(c))
		return (c - '0');
	if (isupper(c))
		c = tolower(c);
	return (c - 'a' + 10);
}

uint8_t	hexToUInt8(const char str[2]) {
	return (charHexToUInt8(str[0]) * 16 + charHexToUInt8(str[1]));
}

t_clr	strToClr(const char str[7]) {
	t_clr	res = {};
	res.r = hexToUInt8(&str[1]);
	res.g = hexToUInt8(&str[3]);
	res.b = hexToUInt8(&str[5]);
	// DEBUG("Clr = #%02X%02X%02X\n", res.r, res.g, res.b);
	return (res);
}

char	*dupAddDotPng(const char *str) {
	static const char	dotPng[] = ".png";

	if (strlen(str) >= strlen(dotPng) && !strcmp(&str[strlen(str) - strlen(dotPng)], dotPng))
		return (strdup(str));
	char *res = malloc(strlen(str) + strlen(dotPng) + 1);
	strcpy(res, str);
	strcat(res, dotPng);
	return (res);
}



int yywrap(void) { return 1; }
 