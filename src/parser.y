%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}

%token DECLBLOCK
%token CODEBLOCK
%token NUMBER
%token FORLOOP
%token WHILELOOP
%token IF
%token ELSE
%token PRINT
%token PRINTLN
%token READ
%token GOTO
%token IDENTIFIER
%token TYPE
%token NEWLINE
%token ETOK
%token EQTO
%token LEQ
%token GEQ
%token NEQ
%token STRINGID
%left '+'
%left '-'
%left '*'
%left '/'
%right '^'

%%

program:		decl_block code_block					/* the program */

decl_block:  	DECLBLOCK '{' declaration '}'
				| DECLBLOCK '{' '}'						/* the declaration block */
				;

code_block:  	CODEBLOCK '{' statements '}'			/* the code block */
				| CODEBLOCK '{' '}'
				;

declaration:   	decl_line declaration					/* declaration block RE */
				| decl_line
				;

decl_line: 		numtype midentifiers term				/* decl line RE */

midentifiers:	identifierdecl ',' midentifiers			/* multiple identifiers RE for commas */
				| identifier
				;

statements:		gotolabel statement_line statements		/* codeblock statements */
				| gotolabel statement_line
				| statement_line statements
				| statement_line
				;

identifier:		IDENTIFIER '[' IDENTIFIER ']'
				| identifierdecl
				;

identifierdecl:	IDENTIFIER '[' NUMBER ']'				/* identifier declaration */
				| IDENTIFIER
				;

mathexp:		mathexp '+' mathexp
				| mathexp '-' mathexp
				| mathexp '*' mathexp
				| mathexp '/' mathexp
				| mathexp '^' mathexp
				| '(' mathexp ')'
				| number
				| identifier
				;

number:			'-' NUMBER
				| NUMBER
				;

assignment:		identifier '=' mathexp

cond_statement: mathexp cond_op mathexp

cond_op:		GEQ
				|LEQ
				|'>'
				|'<'
				|EQTO
				|NEQ
				;

gotoblock:		GOTO IDENTIFIER IF cond_statement
				| GOTO IDENTIFIER
				;

print:			PRINT
				| PRINTLN
				;

term:			NEWLINE

statement_line:	assignment term
				| forloop
				| whileloop
				| ifelse
				| iostatement term
				| gotoblock term
				| term
				;

numtype:		TYPE

gotolabel:		IDENTIFIER ':'

forloop:		FORLOOP forloopdetails '{' statements '}'
				| FORLOOP forloopdetails term
				;

forloopdetails: assignment ',' mathexp ',' mathexp
				| assignment ',' mathexp
				;

whileloop:		WHILELOOP cond_statement '{' statements '}'

ifelse:			IF cond_statement '{' statements '}' ELSE cond_statement '{' statements '}'
				| IF cond_statement '{' statements '}'
				;

iostatement:	print STRINGID ',' midentifiers
				| print midentifiers
				| READ identifier
				;


%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");

	yyparse();
}
