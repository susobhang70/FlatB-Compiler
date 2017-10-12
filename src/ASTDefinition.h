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

class Visitor
{
	public:
		virtual void visit(ASTCodeBlock *) = 0;
		virtual void visit(ASTVariable *) = 0;
		virtual void visit(ASTVariableSet *) = 0;
		virtual void visit(ASTDeclStatement *) = 0;
		virtual void visit(ASTDeclBlock *) = 0;
		virtual void visit(ASTProgram *) = 0;
};

class ASTVisitor: public Visitor
{
	public:
		ASTVisitor();
		void visit(ASTCodeBlock *);
		void visit(ASTVariable *);
		void visit(ASTVariableSet *);
		void visit(ASTDeclStatement *);
		void visit(ASTDeclBlock *);
		void visit(ASTProgram *);
};

class ASTNode
{
	public:
		virtual void accept(Visitor *) = 0;
};

class ASTCodeBlock: public ASTNode
{
	friend class ASTVisitor;
	public:
		ASTCodeBlock();
		void accept(Visitor *);
};

class ASTVariable: public ASTNode
{
	friend class ASTVisitor;
	private:
		string var_name;
		string data_type;
		bool array_type;
		unsigned int length;

	public:
		ASTVariable(string, bool, unsigned int);
		ASTVariable(string, bool);
		void setDataType(string);
		void accept(Visitor *);
};

class ASTVariableSet: public ASTNode
{
	friend class ASTVisitor;
	private:
		vector<ASTVariable *> variables;

	public:
		void addVariable(ASTVariable *);
		vector<ASTVariable *> getVariables();
		void accept(Visitor *);
};

class ASTDeclStatement: public ASTNode
{
	friend class ASTVisitor;
	private:
		vector<ASTVariable *> variables;

	public:
		ASTDeclStatement(string, ASTVariableSet *);
		void accept(Visitor *);
};

class ASTDeclBlock: public ASTNode
{
	friend class ASTVisitor;
	private:
		vector<ASTDeclStatement *> statements;

	public:
		ASTDeclBlock();
		void addStatement(ASTDeclStatement *);
		void accept(Visitor *);
};

class ASTProgram: public ASTNode
{
	friend class ASTVisitor;
	private:
		ASTDeclBlock *decl_block;
		ASTCodeBlock *code_block;

	public:
		ASTProgram(ASTDeclBlock *, ASTCodeBlock *);
		void accept(Visitor *);
};