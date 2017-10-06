#include <iostream>
#include <string>
#include <vector>

using namespace std;

union NODE
{
	int number;
	char *string;
	class ASTCodeBlock *code_statements;
	class ASTVariable *variable;
	class ASTVariableSet *variableSet;
	class ASTDeclStatement *decl_line;
	class ASTDeclBlock *decl_block;
	class ASTProgram *program;

	NODE()
	{
		number = 0;
		string = NULL;
		variable = NULL;
		decl_line = NULL;
		decl_block = NULL;
		program = NULL;
	}
	~NODE()
	{}
};

typedef union NODE YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class ASTNode
{
	public:
		virtual void visit() = 0;
};

class ASTCodeBlock: public ASTNode
{
	public:
		ASTCodeBlock();
		void visit();
};

class ASTVariable: public ASTNode
{
	private:
		string var_name;
		string data_type;
		bool array_type;
		unsigned int length;

	public:
		ASTVariable(string, bool, int);
		ASTVariable(string, bool);
		void setDataType(string);
		void visit();
};

class ASTVariableSet: public ASTNode
{
	private:
		vector<ASTVariable *> variables;

	public:
		void addVariable(ASTVariable *);
		vector<ASTVariable *> getVariables();
		void visit();
};

class ASTDeclStatement: public ASTNode
{
	private:
		vector<ASTVariable *> variables;

	public:
		ASTDeclStatement(string, ASTVariableSet *);
		void visit();
};

class ASTDeclBlock: public ASTNode
{
	private:
		vector<ASTDeclStatement *> statements;

	public:
		ASTDeclBlock();
		void addStatement(ASTDeclStatement *);
		void visit();
};

class ASTProgram: public ASTNode
{
	private:
		ASTDeclBlock *decl_block;
		ASTCodeBlock *code_block;

	public:
		ASTProgram(ASTDeclBlock *, ASTCodeBlock *);
		void visit();
};