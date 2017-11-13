%{
  #include "ASTDefinition.h"
  #include <stdio.h>
  #include <stdlib.h>
  
  #define YYDEBUG 1

  int yylex (void);
  void yyerror (char const *s);
  ASTProgram *start = nullptr;
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
%type <forloop> forloop
%type <whileloop> whileloop
%type <condition> cond_statement
%type <ifelse> ifelse
%type <gotoblock> gotoblock
%type <ioblock> iostatement;

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
%token <string> TYPE IDENTIFIER STRINGID
%token ETOK
%token EQTO
%token LEQ
%token GEQ
%token NEQ

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
					$$ = new ASTProgram($6);
				}
				|DECLBLOCK '{' declaration '}' CODEBLOCK '{' '}'
				{
					$$ = new ASTProgram($3);
				}
				|DECLBLOCK '{' '}' CODEBLOCK '{' '}'
				{
					$$ = new ASTProgram();
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
				;

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

statements:		statements IDENTIFIER ':' statement_line		/* Note to self: include goto */
				{
					$4->setLabel($2);
					$4->setParent($$);
					$$->addStatement($4);
				}
				| IDENTIFIER ':' statement_line
				{
					$$ = new ASTCodeBlock();
					$3->setLabel($1);
					$3->setParent($$);
					$$->addStatement($3);
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

identifier:		IDENTIFIER '[' mathexp ']'
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

mathexp:		mathexp '+' mathexp
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

assignment:		identifier '=' mathexp
				{
					$1->setTarget();
					$$ = new ASTAssignment($1, $3);
				}
				;

cond_statement:	mathexp GEQ mathexp
				{
					$$ = new ASTCondExpr($1, geq, $3);
				}
				| mathexp LEQ mathexp
				{
					$$ = new ASTCondExpr($1, leq, $3);
				}
				| mathexp '>' mathexp
				{
					$$ = new ASTCondExpr($1, grt, $3);
				}
				| mathexp '<' mathexp
				{
					$$ = new ASTCondExpr($1, les, $3);
				}
				| mathexp EQTO mathexp
				{
					$$ = new ASTCondExpr($1, eqto, $3);
				}
				| mathexp NEQ mathexp
				{
					$$ = new ASTCondExpr($1, neq, $3);
				}
				| '!' cond_statement
				{
					$$ = $2;
					$$->flipNot();
				}
				;

gotoblock:		GOTO IDENTIFIER IF cond_statement
				{
					$$ = new ASTGotoBlock($2, $4);
				}
				| GOTO IDENTIFIER
				{
					$$ = new ASTGotoBlock($2);
				}
				;

statement_line:	assignment ';'
				{
					$$ = $1;
				}
				| forloop
				{
					$$ = $1;
				}
				| whileloop
				{
					$$ = $1;
				}
				| ifelse
				{
					$$ = $1;
				}
				| iostatement ';'
				{
					$$ = $1;
				}
				| gotoblock ';'
				{
					$$ = $1;
				}
				;

forloop:		FORLOOP assignment ',' mathexp ',' mathexp '{' statements '}'
				{
					$$ = new ASTForLoop($2, $4, $6, $8);
				}
				| FORLOOP assignment ',' mathexp '{' statements '}'
				{
					$$ = new ASTForLoop($2, $4, $6);
				}
				;

whileloop:		WHILELOOP cond_statement '{' statements '}'
				{
					$$ = new ASTWhileLoop($2, $4);
				}

ifelse:			IF cond_statement '{' statements '}' ELSE '{' statements '}'
				{
					$$ = new ASTIfElse($2, $4, $8);
				}
				| IF cond_statement '{' statements '}'
				{
					$$ = new ASTIfElse($2, $4);
				}
				;

iostatement:	PRINT STRINGID ',' mathexp
				{
					$$ = new ASTIOBlock(print, $2, $4);
				}
				| PRINTLN STRINGID ',' mathexp
				{
					$$ = new ASTIOBlock(println, $2, $4);
				}
				| PRINT STRINGID
				{
					$$ = new ASTIOBlock(print, $2);
				}
				| PRINTLN STRINGID
				{
					$$ = new ASTIOBlock(println, $2);
				}
				| PRINT mathexp
				{
					$$ = new ASTIOBlock(print, $2);
				}
				| PRINTLN mathexp
				{
					$$ = new ASTIOBlock(println, $2);
				}
				| READ identifier
				{
					$2->setTarget();
					$$ = new ASTIOBlock(readvar, $2);
				}
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
		// ASTInterpreter itpr(v.getSymbolTable());
		// itpr.visit(start);
		CodeGenVisitor cgv(v.getSymbolTable());
		cgv.generateCode(start, argv[1]);
	}
}
