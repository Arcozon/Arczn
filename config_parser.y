%{
	#include "type.h"

	#include "start.h"
%}

%union {
	size_t	longval;
	
	t_clr	clrval;
	s_oneClrRules	oneClrRuleval;
	s_clrRules		clrRuleval;
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

void	yyerror (char const s[]) {
	fprintf (stderr, "%s\n", s);
}

void	_annonceSection(void) {
	const e_section sct = parsData.section;
	static const char *sctStr[] = {"text", "data", "bss"};

	if (sct == SCT_NONE || sct > SCT_MAX) {
		exit(255);
	}
	printf("section .%s\n", sctStr[sct - SCT_TEXT]);
}

//__attribute__((format(printf(2, 3))))
static inline void	_writeToSection(const e_section _nSection, const char _format[], va_list vp) {
	if (_nSection != parsData.section) {
		parsData.section = _nSection;
		_annonceSection();
	}
	vprintf(_format, vp);
}

__attribute__((format(printf, 1, 2)))
void	writeText(const char _format[], ...) {
	va_list	 vp;
	va_start(vp, _format);
	_writeToSection(SCT_TEXT, _format, vp);
	va_end(vp);
}

__attribute__((format(printf, 1, 2)))
void	writeData(const char _format[], ...) {
	va_list	 vp;
	va_start(vp, _format);
	_writeToSection(SCT_TEXT, _format, vp);
	va_end(vp);
}

__attribute__((format(printf, 1, 2)))
void	writeBss(const char _format[], ...) {
	va_list	 vp;
	va_start(vp, _format);
	_writeToSection(SCT_TEXT, _format, vp);
	va_end(vp);
}

data_t	parsData =  {0, SCT_NONE};

int main(void) {
	printf(".intel_syntax noprefix\n");
	yyparse();
}
