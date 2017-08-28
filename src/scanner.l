%{
#include "parser.tab.h"
%}

%%

"declblock" {
	printf("Token type: Declaration Block, Lexeme/Token Value: %s\n", yytext);  
	return DECLBLOCK;
}
"codeblock" {
	printf("Token type: Code Block, Lexeme/Token Value: %s\n", yytext);  
	return CODEBLOCK;
}
"int" {
	printf("Token type: Var Type, Lexeme/Token Value: %s\n", yytext);  
	return TYPE;
}
"for" {
	printf("Token type: Forloop, Lexeme/Token Value: %s\n", yytext);  
	return FORLOOP;
}
"while" {
	printf("Token type: Whileloop, Lexeme/Token Value: %s\n", yytext);  
	return WHILELOOP;
}
"if" {
	printf("Token type: If statement, Lexeme/Token Value: %s\n", yytext);  
	return IF;
}
"else" {
	printf("Token type: Else statement, Lexeme/Token Value: %s\n", yytext);  
	return ELSE;
}
"read" {
	printf("Token type: Read statement, Lexeme/Token Value: %s\n", yytext);  
	return READ;
}
"print" {
	printf("Token type: print statement, Lexeme/Token Value: %s\n", yytext);
	return PRINT;
}
"println" {
	printf("Token type: println statement, Lexeme/Token Value: %s\n", yytext);  
	return PRINTLN;
}
"goto" {
	printf("Token type: goto statement, Lexeme/Token Value: %s\n", yytext);  
	return GOTO;
}
[0-9][0-9]*	{  
	printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
	return NUMBER; 
}
[a-zA-Z_]?\"(\\.|[^\\"])*\" {
	printf("Token type: String, Lexeme/Token Value: %s\n", yytext);  
	return STRINGID;
}
[a-zA-Z][a-zA-Z0-9]* {  
	printf("Token type: Identifier, Lexeme/Token Value: %s\n", yytext);  
	return IDENTIFIER; 
} 
"["		return '[';
"]"		return ']';
"{"		return '{';
"}"		return '}';
"*"		return '*';
"/"		return '/';
"+"		return '+';
"-"		return '-';
"^"		return '^';
"=="	return EQTO;
"!="	return NEQ;
">="	return GEQ;
">"		return '>';
"<="	return LEQ;
"<"		return '<';
"="		return '=';
","		return ',';
":"		return ':';
"""		return '"';
";"		return NEWLINE;

[ \t]		{ /* Do nothing */ }
.		{ 
		  printf("Unexpected token encountered: %s\n", yytext); 
		  return ETOK;
		}
