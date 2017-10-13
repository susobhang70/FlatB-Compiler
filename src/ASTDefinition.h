#include <iostream>
#include <string>
#include <vector>

using namespace std;

// enum statement_type {Assignment, Conditional, forloop, whileloop, ifstmt, ifelse};
enum Operation {add, sub, mult, divd, usub, noop};
enum Condition {grt, geq, les, leq, neq, unot};

union NODE
{
	int number;
	char *string;
	class ASTMathExpr *mathexpr;
	class ASTInteger *integer;
	class ASTTargetVar *var_location;
	class ASTAssignment *assignment;
	class ASTCodeStatement *code_statement;
	class ASTCodeBlock *code_block;
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
		virtual void visit(ASTMathExpr *) = 0;
		virtual void visit(ASTInteger *) = 0;
		virtual void visit(ASTTargetVar *) = 0;
		virtual void visit(ASTAssignment *) = 0;
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
		void visit(ASTMathExpr *);
		void visit(ASTInteger *);
		void visit(ASTTargetVar *);
		void visit(ASTAssignment *);
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

class ASTMathExpr: public ASTNode
{
	friend class ASTVisitor;
	protected:
		ASTNode *ltree, *rtree;
		Operation op;
		ASTMathExpr();

	public:
		ASTMathExpr(ASTNode *, ASTNode *, Operation);
		ASTMathExpr(ASTNode *, Operation);
		void accept(Visitor *);
};

class ASTInteger: public ASTMathExpr
{
	friend class ASTVisitor;
	private:
		int lexval;

	public:
		ASTInteger(int);
		void accept(Visitor *);
};

class ASTTargetVar: public ASTMathExpr
{
	friend class ASTVisitor;
	private:
		string var_name;
		bool array_type;

	public:
		ASTTargetVar(string, ASTNode *);
		ASTTargetVar(string, ASTNode *, Operation);
		ASTTargetVar(string);
		ASTTargetVar(string, Operation);
		void setOp(Operation);
		void accept(Visitor *);
};

class ASTCodeStatement: public ASTNode
{
	public:
		void accept(Visitor *);
};

class ASTAssignment: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		ASTTargetVar *target;
		ASTNode *rexpr;

	public:
		ASTAssignment(ASTTargetVar *, ASTNode *);
		void accept(Visitor *);
};

class ASTCodeBlock: public ASTNode
{
	friend class ASTVisitor;
	private:
		vector<ASTCodeStatement *> statements;

	public:
		ASTCodeBlock();
		void addStatement(ASTCodeStatement *);
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