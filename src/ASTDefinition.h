#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Operation {add, sub, mult, divd, usub, noop};
enum Condition {grt, geq, les, leq, neq, eqto};
enum IOInstruction {print, println, readvar};

union NODE
{
	int number;
	char *string;
	class ASTIOBlock *ioblock;
	class ASTGotoBlock *gotoblock;
	class ASTIfElse *ifelse;
	class ASTCondExpr *condition;
	class ASTWhileLoop *whileloop;
	class ASTForLoop *forloop;
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
		string = nullptr;
		ioblock = nullptr;
		gotoblock = nullptr;
		ifelse = nullptr;
		condition = nullptr;
		whileloop = nullptr;
		forloop = nullptr;
		mathexpr = nullptr;
		integer = nullptr;
		var_location = nullptr;
		assignment = nullptr;
		code_statement = nullptr;
		code_block = nullptr;
		variable = nullptr;
		variableSet = nullptr;
		decl_line = nullptr;
		decl_block = nullptr;
		program = nullptr;
	}

	~NODE()
	{}
};

typedef union NODE YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class Visitor
{
	public:
		virtual void visit(ASTIOBlock *) = 0;
		virtual void visit(ASTGotoBlock *) = 0;
		virtual void visit(ASTIfElse *) = 0;
		virtual void visit(ASTCondExpr *) = 0;
		virtual void visit(ASTForLoop *) = 0;
		virtual void visit(ASTWhileLoop *) = 0;
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
		void printLabel(ASTCodeStatement *);
		void visit(ASTIOBlock *);
		void visit(ASTGotoBlock *);
		void visit(ASTIfElse *);
		void visit(ASTCondExpr *);
		void visit(ASTForLoop *);
		void visit(ASTWhileLoop *);
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

class ASTCondExpr: public ASTNode
{
	friend class ASTVisitor;
	private:
		ASTNode *ltree, *rtree;
		Condition condition;
		bool unot;

	public:
		ASTCondExpr(ASTNode *, Condition, ASTNode *);
		void flipNot();
		void accept(Visitor *);
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
		ASTTargetVar(string, Operation);
		ASTTargetVar(string);
		void setOp(Operation);
		void accept(Visitor *);
};

class ASTCodeStatement: public ASTNode
{
	friend class ASTVisitor;
	protected:
		string label;

	public:
		void setLabel(string);
		void accept(Visitor *);
};

class ASTIOBlock: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		IOInstruction iostmt;
		string output;
		ASTMathExpr *expr;

	public:
		ASTIOBlock(IOInstruction, string, ASTMathExpr *);
		ASTIOBlock(IOInstruction, ASTMathExpr *);
		ASTIOBlock(IOInstruction, string);
		ASTIOBlock(IOInstruction);
		void accept(Visitor *);
};

class ASTGotoBlock: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		string targetlabel;
		ASTCondExpr *condition;
	public:
		ASTGotoBlock(string, ASTCondExpr *);
		ASTGotoBlock(string);
		void accept(Visitor *);
};

class ASTIfElse: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		ASTCondExpr *condition;
		ASTNode *iftrue, *iffalse;
	public:
		ASTIfElse(ASTCondExpr *, ASTNode *, ASTNode *);
		ASTIfElse(ASTCondExpr *, ASTNode *);
		void accept(Visitor *);
};

class ASTWhileLoop: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		ASTCondExpr *condition;
		ASTCodeBlock *statements;

	public:
		ASTWhileLoop(ASTCondExpr *, ASTCodeBlock *);
		void accept(Visitor *);		
};

class ASTForLoop: public ASTCodeStatement
{
	friend class ASTVisitor;
	private:
		ASTAssignment *assignment;
		ASTMathExpr *ulimit, *increment;
		ASTCodeBlock *statements;

	public:
		ASTForLoop(ASTAssignment *, ASTMathExpr *, ASTMathExpr *, ASTCodeBlock *);
		ASTForLoop(ASTAssignment *, ASTMathExpr *, ASTCodeBlock *);
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
		ASTProgram(ASTDeclBlock *);
		ASTProgram(ASTCodeBlock *);
		ASTProgram();
		void accept(Visitor *);
};