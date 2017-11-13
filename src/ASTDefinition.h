#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

using namespace std;
using namespace llvm;

enum Operation {add, sub, mult, divd, usub, noop};
enum Condition {grt, geq, les, leq, neq, eqto};
enum IOInstruction {print, println, readvar};

// This is the union NODE, which will be used in bison
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

// The base virtual class for Visitor Design Pattern
class Visitor
{
	public:
		virtual void visit(ASTIOBlock 		*) = 0;
		virtual void visit(ASTGotoBlock 	*) = 0;
		virtual void visit(ASTIfElse 		*) = 0;
		virtual void visit(ASTCondExpr 		*) = 0;
		virtual void visit(ASTForLoop 		*) = 0;
		virtual void visit(ASTWhileLoop 	*) = 0;
		virtual void visit(ASTMathExpr 		*) = 0;
		virtual void visit(ASTInteger 		*) = 0;
		virtual void visit(ASTTargetVar 	*) = 0;
		virtual void visit(ASTAssignment 	*) = 0;
		virtual void visit(ASTCodeBlock 	*) = 0;
		virtual void visit(ASTVariable 		*) = 0;
		virtual void visit(ASTVariableSet 	*) = 0;
		virtual void visit(ASTDeclStatement *) = 0;
		virtual void visit(ASTDeclBlock 	*) = 0;
		virtual void visit(ASTProgram 		*) = 0;

		virtual bool visit_value(ASTCondExpr *) = 0;
		virtual int  visit_value(ASTMathExpr *) = 0;
		virtual int  visit_value(ASTTargetVar*) = 0;
		virtual int  visit_value(ASTInteger  *) = 0;
		virtual void visit_value(ASTTargetVar*, int) = 0;
};

class ASTNode
{
	protected:
		ASTNode *parent;

	public:
		void setParent(ASTNode *);
		ASTNode* getParent();
		virtual void accept(Visitor *) = 0;
		virtual Value* codegen(class CodeGenVisitor *) = 0;
};

// Symbol Table Entry class, whose objects will be stored in a map
class SymbolTableEntry
{
	private:
		string identifier;
		unsigned int size;
		int *value;
		ASTCodeStatement *node;

	public:
		bool isArray;
		SymbolTableEntry(string, unsigned int);
		SymbolTableEntry(string);
		SymbolTableEntry(string, ASTCodeStatement*);
		ASTCodeStatement* getLabelPtr();
		int getValue(unsigned int);
		int getValue();
		void setValue(unsigned int, int);
		void setValue(int);
};

class CodeGenVisitor
{
	private:
		stack<BasicBlock *> blocks;
		map<string, Value*> variables;
		map<string, BasicBlock*> labels;
		map<string, SymbolTableEntry *> symboltable;
		Function *mainFunction;
		Function *Print, *Scan;
		int errors;

	public:
		CodeGenVisitor(map<string, SymbolTableEntry *> st);
		void generateCode(ASTProgram*, string);
		BasicBlock *currentBlock() { return blocks.top(); }
		void pushBlock(BasicBlock *block) {blocks.push(block); }
		void popBlock() { blocks.pop(); }

		Value* checkLabel(ASTCodeStatement*);
		Value* visit(ASTIOBlock 		*);
		Value* visit(ASTGotoBlock 		*);
		Value* visit(ASTIfElse 			*);
		Value* visit(ASTCondExpr 		*);
		Value* visit(ASTForLoop 		*);
		Value* visit(ASTWhileLoop 		*);
		Value* visit(ASTMathExpr 		*);
		Value* visit(ASTInteger 		*);
		Value* visit(ASTTargetVar 		*);
		Value* visit(ASTAssignment 		*);
		Value* visit(ASTCodeBlock 		*);
		Value* visit(ASTVariable 		*);
		Value* visit(ASTVariableSet 	*);
		Value* visit(ASTDeclStatement 	*);
		Value* visit(ASTDeclBlock 		*);
		Value* visit(ASTProgram 		*);
};

// The derived ASTVisitor class for outputting the AST to XML
class ASTVisitor: public Visitor
{
	private:
		map<string, SymbolTableEntry *> symboltable;

	public:
		ASTVisitor();
		void printLabel(ASTCodeStatement *);
		map<string, SymbolTableEntry *> getSymbolTable();

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

		bool visit_value(ASTCondExpr *) { return true; }
		int  visit_value(ASTMathExpr *) { return 0; }
		int  visit_value(ASTTargetVar*) { return 0; }
		int  visit_value(ASTInteger  *) { return 0; }
		void visit_value(ASTTargetVar*, int) { return; }
};

// The derived ASTInterpreter class for interpreter
class ASTInterpreter: public Visitor
{
	private:
		map<string, SymbolTableEntry *> symboltable;
		ASTCodeStatement *nextGotoNode;

	public:
		ASTInterpreter(map<string, SymbolTableEntry *>);
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

		bool visit_value(ASTCondExpr *);
		int  visit_value(ASTMathExpr *);
		int  visit_value(ASTTargetVar*);
		int  visit_value(ASTInteger  *);
		void visit_value(ASTTargetVar*, int);
};

class ASTCondExpr: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTMathExpr *ltree, *rtree;
		Condition condition;
		bool unot;

	public:
		ASTCondExpr(ASTMathExpr *, Condition, ASTMathExpr *);
		void flipNot();
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
		bool accept_value(Visitor *);
};

class ASTMathExpr: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	protected:
		ASTMathExpr *ltree, *rtree;
		Operation op;
		ASTMathExpr();

	public:
		ASTMathExpr(ASTMathExpr *, ASTMathExpr *, Operation);
		ASTMathExpr(ASTMathExpr *, Operation);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
		virtual int accept_value(Visitor *);
};

class ASTInteger: public ASTMathExpr
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		int lexval;

	public:
		ASTInteger(int);
		int getValue();
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
		int  accept_value(Visitor *);
};

class ASTTargetVar: public ASTMathExpr
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		string var_name;
		bool array_type;
		bool isTarget;

	public:
		ASTTargetVar(string, ASTMathExpr *);
		ASTTargetVar(string, ASTMathExpr *, Operation);
		ASTTargetVar(string, Operation);
		ASTTargetVar(string);
		void setOp(Operation);
		void setTarget() { isTarget = true; }
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
		int  accept_value(Visitor *);
		void accept_value(Visitor *, int);
};

class ASTCodeStatement: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	protected:
		string label;

	public:
		void setLabel(string);
		void accept(Visitor *);
};

class ASTIOBlock: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
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
		Value* codegen(CodeGenVisitor*);
};

class ASTGotoBlock: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		string targetlabel;
		ASTCondExpr *condition;
	public:
		ASTGotoBlock(string, ASTCondExpr *);
		ASTGotoBlock(string);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTIfElse: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTCondExpr *condition;
		ASTCodeBlock *iftrue, *iffalse;
	public:
		ASTIfElse(ASTCondExpr *, ASTCodeBlock *, ASTCodeBlock *);
		ASTIfElse(ASTCondExpr *, ASTCodeBlock *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTWhileLoop: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTCondExpr *condition;
		ASTCodeBlock *statements;

	public:
		ASTWhileLoop(ASTCondExpr *, ASTCodeBlock *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);		
};

class ASTForLoop: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTAssignment *assignment;
		ASTMathExpr *ulimit, *increment;
		ASTCodeBlock *statements;

	public:
		ASTForLoop(ASTAssignment *, ASTMathExpr *, ASTMathExpr *, ASTCodeBlock *);
		ASTForLoop(ASTAssignment *, ASTMathExpr *, ASTCodeBlock *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTAssignment: public ASTCodeStatement
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTTargetVar *target;
		ASTMathExpr *rexpr;

	public:
		ASTAssignment(ASTTargetVar *, ASTMathExpr *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTCodeBlock: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		vector<ASTCodeStatement *> statements;

	public:
		ASTCodeBlock();
		void addStatement(ASTCodeStatement *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTVariable: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
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
		Value* codegen(CodeGenVisitor*);
};

class ASTVariableSet: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		vector<ASTVariable *> variables;

	public:
		void addVariable(ASTVariable *);
		vector<ASTVariable *> getVariables();
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTDeclStatement: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		vector<ASTVariable *> variables;

	public:
		ASTDeclStatement(string, ASTVariableSet *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTDeclBlock: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		vector<ASTDeclStatement *> statements;

	public:
		ASTDeclBlock();
		void addStatement(ASTDeclStatement *);
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};

class ASTProgram: public ASTNode
{
	friend class ASTVisitor;
	friend class ASTInterpreter;
	friend class CodeGenVisitor;
	private:
		ASTDeclBlock *decl_block;
		ASTCodeBlock *code_block;

	public:
		ASTProgram(ASTDeclBlock *, ASTCodeBlock *);
		ASTProgram(ASTDeclBlock *);
		ASTProgram(ASTCodeBlock *);
		ASTProgram();
		void accept(Visitor *);
		Value* codegen(CodeGenVisitor*);
};