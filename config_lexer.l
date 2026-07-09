%{
	#include <ctype.h>
	#include "config_parser.h"
%}

%%

"point"		{	return (START_POINT);	}
"n_point"	{	return (N_POINT);	}

"type"		{	return (TYPE);	}

"red"	{	return (RED);	}
"green"	{	return (GREEN);	}
"blue"	{	return (BLUE);	}

"min"	{	return (MIN);	}
"max"	{	return (MAX);	}
"delta"	{	return (DELTA);	}


[0-9]+	{		yylval.longval = strtol(yytext, NULL, 10);		return(INT);	}

%%

int yywrap(void) { return 1; }
