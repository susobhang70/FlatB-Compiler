bcc:	parser.tab.c lex.yy.c
	g++ parser.tab.c lex.yy.c ASTDefinition.cpp CodeGen.cpp -g -O0 -std=c++11 -lfl  -o bcc `llvm-config-3.9 --cppflags --libs all --ldflags --system-libs`
parser.tab.c: parser.y 
	bison -d parser.y 
parser.tab.h: parser.y
	bison -d parser.y 
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean 
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true