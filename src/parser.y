%{
  #include "ASTDefinition.h"
  #include <stdio.h>
  #include <stdlib.h>
  
  #define YYDEBUG 1

  int yylex (void);
  void yyerror (char const *s);
  ASTProgram *start = NULL;
%}

%type <program> program
%type <decl_block> declaration
%type <decl_line> decl_line
%type <variableSet> midentifiers
%type <variable> identifierdecl
%type <code_block> statements
%type <code_statement> statement_line
%type <assignment> assignment
%type <var_location> identifier
%type <mathexpr> mathexp

%token DECLBLOCK
%token CODEBLOCK
%token <number> NUMBER
%token FORLOOP
%token WHILELOOP
%token IF
%token ELSE
%token PRINT
%token PRINTLN
%token READ
%token GOTO
%token <string> TYPE IDENTIFIER
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

program:		DECLBLOCK '{' declaration '}' CODEBLOCK '{' statements '}'
				{
					$$ = new ASTProgram($3, $7);
					start = $$;
				}
				| DECLBLOCK '{' '}'	CODEBLOCK '{' statements '}'
				{
					$$ = new ASTProgram(NULL, $6);
				}
				|DECLBLOCK '{' declaration '}' CODEBLOCK '{' '}'
				{
					$$ = new ASTProgram($3, NULL);
				}
				|DECLBLOCK '{' '}' CODEBLOCK '{' '}'
				{
					$$ = new ASTProgram(NULL, NULL);
				}
				;

declaration:	decl_line
				{
					$$ = new ASTDeclBlock();
					$$->addStatement($1);
				}
				| declaration decl_line 
				{
					$$->addStatement($2);
				}
				;

decl_line: 		TYPE midentifiers ';'				/* decl line RE */
				{
					$$ = new ASTDeclStatement(string($1), $2);
				}
				| error ';'
				{
					yyerrok;
				}

midentifiers:	identifierdecl
				{
					$$ = new ASTVariableSet();
					$$->addVariable($1);
				}
				| midentifiers ',' identifierdecl
				{
					$$->addVariable($3);
				}
				;

statements:		statements gotolabel statement_line		/* Note to self: Correction - This actually works */
				{
					$$->addStatement($3);
				}
				| gotolabel statement_line
				{
					$$ = new ASTCodeBlock();
					$$->addStatement($2);
				}
				| statements statement_line
				{
					$$->addStatement($2);
				}
				| statement_line
				{
					$$ = new ASTCodeBlock();
					$$->addStatement($1);
				}
				;

identifier:		IDENTIFIER '[' mathexp ']'			/* Note to self: make this mathexp instead of IDENTIFIER */
				{
					$$ = new ASTTargetVar($1, $3);
				}
				| IDENTIFIER
				{
					$$ = new ASTTargetVar($1);
				}
				;

identifierdecl:	IDENTIFIER '[' NUMBER ']'				/* identifier declaration */
				{
					$$ = new ASTVariable(string($1), true, $3);
				}
				| IDENTIFIER
				{
					$$ = new ASTVariable(string($1), false);
				}
				;

mathexp:		mathexp '+' mathexp						/* Note to self: Accept unary statements here - Update: done */
				{
					$$ = new ASTMathExpr($1, $3, add);
				}
				| mathexp '-' mathexp
				{
					$$ = new ASTMathExpr($1, $3, sub);
				}
				| mathexp '*' mathexp
				{
					$$ = new ASTMathExpr($1, $3, mult);
				}
				| mathexp '/' mathexp
				{
					$$ = new ASTMathExpr($1, $3, divd);
				}
				| '(' mathexp ')'
				{
					$$ = new ASTMathExpr($2, noop);
				}
				| NUMBER
				{
					$$ = new ASTInteger($1);
				}
				| '-' NUMBER
				{
					$$ = new ASTInteger(-$2);
				}
				| '-' identifier
				{
					$2->setOp(usub);
					$$ = $2;
				}
				| identifier
				{
					$$ = $1;
				}
				;

assignment:		identifier '=' assignment
				{
					$$ = new ASTAssignment($1, $3);
				}
				| identifier '=' mathexp
				{
					$$ = new ASTAssignment($1, $3);
				}
				;

cond_statement:	mathexp cond_op cond_statement
				| mathexp cond_op mathexp
				;

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

statement_line:	assignment ';'
				{
					$$ = $1;
				}
				| forloop
				{
					$$ = new ASTCodeStatement();
				}
				| whileloop
				{
					$$ = new ASTCodeStatement();
				}
				| ifelse
				{
					$$ = new ASTCodeStatement();
				}
				| iostatement ';'
				{
					$$ = new ASTCodeStatement();
				}
				| gotoblock ';'
				{
					$$ = new ASTCodeStatement();
				}
				| ';'
				{
					$$ = new ASTCodeStatement();
				}
				;

gotolabel:		IDENTIFIER ':'

forloop:		FORLOOP forloopdetails '{' statements '}'
				| FORLOOP forloopdetails ';'
				;

forloopdetails:	assignment ',' mathexp ',' mathexp
				| assignment ',' mathexp
				;

whileloop:		WHILELOOP cond_statement '{' statements '}'

ifelse:			IF cond_statement '{' statements '}' ELSE '{' statements '}'
				| IF cond_statement '{' statements '}'
				;

iostatement:	print STRINGID ',' midentifiers
				| print STRINGID
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
	extern FILE *yyin;
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

	if(start)
	{
		ASTVisitor v;
		v.visit(start);
	}
}
