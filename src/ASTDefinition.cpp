#include "ASTDefinition.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>

using namespace std;

ofstream xml("AST_XML.xml");
int tabs = 0;
ASTCodeStatement *currentStatement = nullptr;

struct GotoException : public exception 
{
	const char* what() const throw () 
	{
		return "Goto Exception";
	}
};

void insertTabs()
{
	for(int i = 0; i < tabs; i++)
		xml << "\t";
}

string toStringOperation(Operation op)
{
	switch(op)
	{
		case add:
			return "+";
			break;

		case sub:
			return "-";
			break;

		case mult:
			return "*";
			break;

		case divd:
			return "/";
			break;

		case usub:
			return "usub";
			break;

		case noop:
			return "";
			break;
	}
}

string toStringCondition(Condition cond)
{
	switch(cond)
	{
		case grt:
			return ">";
			break;

		case geq:
			return ">=";
			break;
		
		case les:
			return "<";
			break;
		
		case leq:
			return "<=";
			break;
		
		case neq:
			return "!=";
			break;
		
		case eqto:
			return "==";
			break;
	}
}

string toStringIOStmt(IOInstruction iostmt)
{
	switch(iostmt)
	{
		case print:
			return "print";
			break;

		case println:
			return "println";
			break;
		
		case readvar:
			return "read";
			break;
	}
}

/*************************** ASTNode ********************************/
void ASTNode::setParent(ASTNode *parent)
{
	this->parent = parent;
}

ASTNode* ASTNode::getParent()
{
	return parent;
}

/************************** End ASTNode *****************************/

/*************************** ASTVisitor **************************************/
ASTVisitor::ASTVisitor()
{
	return;
}

void ASTVisitor::printLabel(ASTCodeStatement *statement)
{
	if(!statement->label.empty())
	{
		if(symboltable.find(statement->label) == symboltable.end())
		{
			insertTabs();
			xml << "<label name=\'" << statement->label << "\' />" << endl;
			SymbolTableEntry *ste = new SymbolTableEntry(statement->label, statement);
			symboltable[statement->label] = ste;
		}
		else
		{
			cerr << "[ERROR] Label " << statement->label << " defined before" << endl;
			exit(1);
		}
	}
}

void ASTVisitor::visit(ASTIOBlock *ioblock)
{
	printLabel(ioblock);
	insertTabs();
	xml << "<" << toStringIOStmt(ioblock->iostmt) << ">" << endl;

	tabs++;
	if(!ioblock->output.empty())
	{
		insertTabs();
		xml << "<string value=\'" << ioblock->output << "\' />" << endl;
	}
	if(ioblock->expr)
		ioblock->expr->accept(this);
	tabs--;

	insertTabs();
	xml << "</" << toStringIOStmt(ioblock->iostmt) << ">" << endl;	
}

void ASTVisitor::visit(ASTGotoBlock *gotoblock)
{
	printLabel(gotoblock);
	insertTabs();
	xml << "<goto label=\'" << gotoblock->targetlabel << "\'";
	if(gotoblock->condition)
	{
		xml << ">" << endl;
		tabs++;
		gotoblock->condition->accept(this);
		tabs--;
		insertTabs();
		xml << "</goto>" << endl;
	}
	else
		xml << " />" << endl;
}

void ASTVisitor::visit(ASTIfElse *ifelse)
{
	printLabel(ifelse);
	insertTabs();
	xml << "<ifelseblock>" << endl;
	tabs++;
	ifelse->condition->accept(this);
	insertTabs();
	xml << "<if>" << endl;
	tabs++;
	ifelse->iftrue->accept(this);
	tabs--;
	insertTabs();
	xml << "</if>" << endl;
	if(ifelse->iffalse)
	{
		insertTabs();
		xml << "<else>" << endl;
		tabs++;
		ifelse->iffalse->accept(this);
		tabs--;
		insertTabs();
		xml << "</else>" << endl;
	}
	tabs--;
	insertTabs();
	xml << "</ifelseblock>" << endl;
}

void ASTVisitor::visit(ASTCondExpr *condition)
{
	insertTabs();
	xml << "<condition unot=\'" << condition->unot << "\' operation=\'";
	xml << toStringCondition(condition->condition) << "\'>" << endl;
	tabs++;
	condition->ltree->accept(this);
	condition->rtree->accept(this);
	tabs--;
	insertTabs();
	xml << "</condition>" << endl;
}

void ASTVisitor::visit(ASTWhileLoop *whileloop)
{
	printLabel(whileloop);
	insertTabs();
	xml << "<whileloop>" << endl;
	tabs++;
	whileloop->condition->accept(this);
	whileloop->statements->accept(this);
	tabs--;
	insertTabs();
	xml << "</whileloop>" << endl;
}

void ASTVisitor::visit(ASTForLoop *forloop)
{
	printLabel(forloop);
	insertTabs();
	xml << "<forloop>" << endl;
	tabs++;
	insertTabs();
	xml << "<init>" << endl;
	tabs++;
	forloop->assignment->accept(this);
	tabs--;
	insertTabs();
	xml << "</init>" << endl;
	insertTabs();
	xml << "<limit>" << endl;
	tabs++;
	forloop->ulimit->accept(this);
	tabs--;
	insertTabs();
	xml << "<limit>" << endl;
	if(forloop->increment)
	{
		insertTabs();
		xml << "<increment>" << endl;
		tabs++;
		forloop->increment->accept(this);
		tabs--;
		insertTabs();
		xml << "</increment>" << endl;
	}
	forloop->statements->accept(this);
	tabs--;
	insertTabs();
	xml << "</forloop>" << endl;
}

void ASTVisitor::visit(ASTMathExpr *mathexpr)
{
	insertTabs();
	xml << "<mathexpr operation=\'";
	xml << toStringOperation(mathexpr->op) << "\'>" << endl;
	tabs++;
	if(mathexpr->ltree)
		mathexpr->ltree->accept(this);
	if(mathexpr->rtree)
		mathexpr->rtree->accept(this);
	tabs--;
	insertTabs();
	xml << "</mathexpr>" << endl;
}

void ASTVisitor::visit(ASTInteger *integer)
{
	insertTabs();
	xml << "<integer value=\'" << integer->lexval << "\' />" << endl;
}

void ASTVisitor::visit(ASTTargetVar *var_location)
{
	if(symboltable.find(var_location->var_name) == symboltable.end())
	{
		cerr << "[ERROR] Variable " << var_location->var_name 
									<< " not defined" << endl;
		exit(1);
	}

	insertTabs();
	xml << "<var_location name=\'" << var_location->var_name << "\' ";

	if(var_location->op != noop)
		xml << "operation=\'" << toStringOperation(var_location->op) <<"\' ";

	if(var_location->array_type)
	{
		tabs++;
		xml << ">" << endl;
		insertTabs();
		xml << "<index>" << endl;
		tabs++;
		var_location->rtree->accept(this);
		tabs--;
		insertTabs();
		xml << "</index>" << endl;
		tabs--;
		insertTabs();
		xml << "</var_location>" << endl;
	}
	else
		xml << "/>" << endl;
}

void ASTVisitor::visit(ASTAssignment *assignment)
{
	printLabel(assignment);
	insertTabs();
	xml << "<equals>" << endl;
	tabs++;
	assignment->target->accept(this);
	assignment->rexpr->accept(this);
	tabs--;
	insertTabs();
	xml << "</equals>" << endl;
}

void ASTVisitor::visit(ASTCodeBlock *code_block)
{
	insertTabs();
	xml << "<code>" << endl;
	tabs++;
	for(auto statement: code_block->statements)
		statement->accept(this);
	tabs--;
	insertTabs();
	xml << "</code>" << endl;
}

void ASTVisitor::visit(ASTVariable *variable)
{
	if(symboltable.find(variable->var_name) == symboltable.end())
	{
		insertTabs();
		SymbolTableEntry *ste;
		xml << "<variable name=\'" << variable->var_name << "\' ";
		if(variable->array_type)
		{
			xml << "size=\'" << variable->length << "\' ";
			ste = new SymbolTableEntry(variable->var_name, variable->length);
		}
		else
			ste = new SymbolTableEntry(variable->var_name);
		xml << "type=\'" << variable->data_type << "\' />" << endl;

		symboltable[variable->var_name] = ste;
	}
	else
	{
		cerr << "[ERROR] Multiple variable declarations of " << variable->var_name << endl;
		exit(1);
	}
}

void ASTVisitor::visit(ASTVariableSet *variableSet)
{
	for(auto variable: variableSet->variables)
		variable->accept(this);
}

void ASTVisitor::visit(ASTDeclStatement *decl_line)
{
	for(auto variable: decl_line->variables)
		variable->accept(this);
}

void ASTVisitor::visit(ASTDeclBlock *decl_block)
{
	insertTabs();
	xml << "<declarations>" << endl;
	tabs++;
	for(auto statement: decl_block->statements)
		statement->accept(this);
	tabs--;
	insertTabs();
	xml << "</declarations>" << endl;
}

void ASTVisitor::visit(ASTProgram *program)
{
	xml << "<?xml version=\'1.0\' encoding=\'UTF-8\'?>" << endl;
	xml << "<program language=\'Flat-B\'>" << endl;
	tabs++;
	if(program->decl_block)				// could be that there is no decl block
		program->decl_block->accept(this);
	if(program->code_block)				// could be that there is no code block
		program->code_block->accept(this);
	tabs--;
	xml << "</program>" << endl;
}

map<string, SymbolTableEntry *> ASTVisitor::getSymbolTable()
{
	return this->symboltable;
}

/************************** End ASTVisitor ***********************************/

/*************************** SymbolTableEntry ********************************/
SymbolTableEntry::SymbolTableEntry(string identifier, unsigned int size)
{
	this->identifier = identifier;
	this->isArray = true;
	this->size = size;
	this->value = new int[size];
	this->node = nullptr;
}

SymbolTableEntry::SymbolTableEntry(string identifier)
{
	this->identifier = identifier;
	this->isArray = false;
	this->value = new int[1];
	this->node = nullptr;
}

SymbolTableEntry::SymbolTableEntry(string identifier, ASTCodeStatement *node)
{
	this->identifier = identifier;
	this->isArray = false;
	this->value = nullptr;
	this->node = node;
}

int SymbolTableEntry::getValue(unsigned int index)
{
	if(isArray)
	{
		if(index < size)
		{
			return value[index];
		}
		else
		{
			cout << "Array index out of bounds" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Identifier is not an array" << endl;
		exit(1);
	}
}

void SymbolTableEntry::setValue(unsigned int index, int lexval)
{
	if(isArray)
	{
		if(index < size)
		{
			value[index] = lexval;
		}
		else
		{
			cout << "Array index out of bounds" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Identifier is not an array" << endl;
		exit(1);
	}
}

int SymbolTableEntry::getValue()
{
	if(!isArray)
	{
		if(value)
		{
			return value[0];
		}
		else
		{
			cout << "Variable declared as label" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Identifier is an array" << endl;
		exit(1);
	}
}

void SymbolTableEntry::setValue(int lexval)
{
	if(!isArray)
	{
		if(value)
		{
			value[0] = lexval;
		}
		else
		{
			cout << "Variable declared as label" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Identifier is an array" << endl;
		exit(1);
	}
}

ASTCodeStatement* SymbolTableEntry::getLabelPtr()
{
	if(!isArray)
	{
		if(value == nullptr)
		{
			return node;
		}
		else
		{
			cout << "Identifier is a variable, not a label" << endl;
			exit(1);
		}
	}
	else
	{
		cout << "Identifier is a variable" << endl;
		exit(1);
	}
}

/************************** End SymbolTableEntry *****************************/

/*************************** ASTInterpreter **********************************/
ASTInterpreter::ASTInterpreter(map<string, SymbolTableEntry *> symboltable)
{
	this->symboltable = symboltable;
}

void ASTInterpreter::visit(ASTIOBlock *ioblock)
{
	if(ioblock->iostmt == readvar)
	{
		int input;
		cin >> input;

		ASTTargetVar *target = static_cast<ASTTargetVar *>(ioblock->expr);
		target->accept_value(this, input);
	}
	else
	{
		if(!ioblock->output.empty())
			cout << ioblock->output;

		if(ioblock->expr)
			cout << ioblock->expr->accept_value(this);

		if(ioblock->iostmt == println)
			cout << endl;
	}
}

void ASTInterpreter::visit(ASTGotoBlock *gotoblock)
{
	if(gotoblock->condition)
	{
		if(gotoblock->condition->accept_value(this))
		{
			nextGotoNode = symboltable[gotoblock->targetlabel]->getLabelPtr();
			throw GotoException();
		}
	}
	else
	{
		nextGotoNode = symboltable[gotoblock->targetlabel]->getLabelPtr();
		throw GotoException();
	}
}

void ASTInterpreter::visit(ASTIfElse *ifelse)
{
	if(ifelse->condition->accept_value(this))
	{
		if(ifelse->iftrue)
			ifelse->iftrue->accept(this);
	}
	else
	{
		if(ifelse->iffalse)
			ifelse->iffalse->accept(this);
	}
}

bool ASTInterpreter::visit_value(ASTCondExpr *condition)
{
	int ltree_val = condition->ltree->accept_value(this);
	int rtree_val = condition->rtree->accept_value(this);

	bool outcome;

	switch(condition->condition)
	{
		case grt:
			outcome = ltree_val > rtree_val;
			break;

		case geq:
			outcome = ltree_val >= rtree_val;
			break;
		
		case les:
			outcome = ltree_val < rtree_val;
			break;
		
		case leq:
			outcome = ltree_val <= rtree_val;
			break;
		
		case neq:
			outcome = ltree_val != rtree_val;
			break;
		
		case eqto:
			outcome = ltree_val == rtree_val;
			break;		
	}

	if(condition->unot)
		return !outcome;

	return outcome;
}

void ASTInterpreter::visit(ASTCondExpr *condition)
{
	return;
}

void ASTInterpreter::visit(ASTWhileLoop *whileloop)
{
	while(whileloop->condition->accept_value(this))
	{
		whileloop->statements->accept(this);
	}
}

void ASTInterpreter::visit(ASTForLoop *forloop)
{
	forloop->assignment->accept(this);

	int i = forloop->assignment->target->accept_value(this);
	int ulimit = forloop->ulimit->accept_value(this);

	while(i < ulimit)
	{
		forloop->statements->accept(this);
		ulimit = forloop->ulimit->accept_value(this);
		if(forloop->increment)
			i += forloop->increment->accept_value(this);
		else
			i += 1;
		forloop->assignment->target->accept_value(this, i);
	}
}


int ASTInterpreter::visit_value(ASTMathExpr *mathexpr)
{
	int ltree_val = 0, rtree_val = 0;
	if(mathexpr->ltree)
		ltree_val = mathexpr->ltree->accept_value(this);
	if(mathexpr->rtree)
		rtree_val = mathexpr->rtree->accept_value(this);
	
	switch(mathexpr->op)
	{
		case add:
			return ltree_val + rtree_val;
			break;

		case sub:
			return ltree_val - rtree_val;
			break;

		case mult:
			return ltree_val * rtree_val;
			break;

		case divd:
			return ltree_val / rtree_val;
			break;

		case usub:
			return -rtree_val;
			break;

		case noop:
			return rtree_val;
			break;
	}
}

void ASTInterpreter::visit(ASTMathExpr *mathexpr)
{
	return;
}

int ASTInterpreter::visit_value(ASTInteger *integer)
{
	return integer->getValue();
}

void ASTInterpreter::visit(ASTInteger *integer)
{
	return;
}

void ASTInterpreter::visit_value(ASTTargetVar *var_location, int value)
{
	if(var_location->array_type)
	{
		int index = var_location->rtree->accept_value(this);
		symboltable[var_location->var_name]->setValue(index, value);
	}
	else
		symboltable[var_location->var_name]->setValue(value);
}

int ASTInterpreter::visit_value(ASTTargetVar *var_location)
{
	int sign = 1;

	if(var_location->op == usub)
		sign = -1;

	if(var_location->array_type)
	{
		int index = var_location->rtree->accept_value(this);
		return sign * symboltable[var_location->var_name]->getValue(index);
	}
	else
		return sign * symboltable[var_location->var_name]->getValue();
}

void ASTInterpreter::visit(ASTTargetVar *var_location)
{
	return;
}

void ASTInterpreter::visit(ASTAssignment *assignment)
{
	int rexpr_value = assignment->rexpr->accept_value(this);
	assignment->target->accept_value(this, rexpr_value);
}

void ASTInterpreter::visit(ASTCodeBlock *code_block)
{
	for(vector<ASTCodeStatement *>::iterator it = code_block->statements.begin(); 
		it != code_block->statements.end(); ++it)
	{
		try
		{
			(*it)->accept(this);
		}
		catch (GotoException& e)
		{
			it = find(code_block->statements.begin(), 
						code_block->statements.end(), this->nextGotoNode);

			if(it == code_block->statements.end())
				throw GotoException();

			--it;
		}
	}
}

void ASTInterpreter::visit(ASTVariable *variable)
{
	return;
}

void ASTInterpreter::visit(ASTVariableSet *variableSet)
{
	return;
}

void ASTInterpreter::visit(ASTDeclStatement *decl_line)
{
	return;
}

void ASTInterpreter::visit(ASTDeclBlock *decl_block)
{
	return;
}

void ASTInterpreter::visit(ASTProgram *program)
{
	cout << "------------------- INTERPRETER ------------------------" << endl;
	if(program->code_block)
	{
		try
		{
			program->code_block->accept(this);
		}
		catch (GotoException& e)
		{
			cerr << "[ERROR] Goto with wrong scope" << endl;
		}
	}
}

/************************** End ASTInterpreter *******************************/

/*************************** ASTIOBlock **************************************/
ASTIOBlock::ASTIOBlock(IOInstruction iostmt, string output, ASTMathExpr *expr)
{
	this->iostmt = iostmt;
	this->output = output.substr(1, output.size() - 2);  // to remove quotes
	this->expr = expr;
}

ASTIOBlock::ASTIOBlock(IOInstruction iostmt, ASTMathExpr *expr)
{
	this->iostmt = iostmt;
	this->expr = expr;
}

ASTIOBlock::ASTIOBlock(IOInstruction iostmt, string output): 
							ASTIOBlock(iostmt, output, nullptr)
{}

ASTIOBlock::ASTIOBlock(IOInstruction iostmt): ASTIOBlock(iostmt, nullptr)
{}

void ASTIOBlock::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTIOBlock::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTIOBlock ***********************************/

/*************************** ASTGotoBlock ************************************/
ASTGotoBlock::ASTGotoBlock(string targetlabel, ASTCondExpr *condition)
{
	this->targetlabel = targetlabel;
	this->condition = condition;
}

ASTGotoBlock::ASTGotoBlock(string targetlabel): 
									ASTGotoBlock(targetlabel, nullptr)
{}

void ASTGotoBlock::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTGotoBlock::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTGotoBlock *********************************/

/*************************** ASTIfElse ***************************************/
ASTIfElse::ASTIfElse(ASTCondExpr *condition, ASTCodeBlock *iftrue, ASTCodeBlock *iffalse)
{
	this->condition = condition;
	this->iftrue = iftrue;
	this->iffalse = iffalse;
}

ASTIfElse::ASTIfElse(ASTCondExpr *condition, ASTCodeBlock *iftrue):
										ASTIfElse(condition, iftrue, nullptr)
{}

void ASTIfElse::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTIfElse::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTIfElse ************************************/

/*************************** ASTInteger **************************************/

ASTInteger::ASTInteger(int lexval)
{
	this->lexval = lexval;
}

int ASTInteger::getValue()
{
	return this->lexval;
}

void ASTInteger::accept(Visitor *v)
{
	v->visit(this);
}

int ASTInteger::accept_value(Visitor *v)
{
	return v->visit_value(this);
}

Value *ASTInteger::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTInteger ***********************************/

/*************************** ASTCondExpr *************************************/
ASTCondExpr::ASTCondExpr(ASTMathExpr *ltree, Condition condition, ASTMathExpr *rtree)
{
	this->ltree = ltree;
	this->rtree = rtree;
	this->condition = condition;
	this->unot = false;
}

void ASTCondExpr::flipNot()
{
	this->unot = !this->unot;
}

void ASTCondExpr::accept(Visitor *v)
{
	v->visit(this);
}

bool ASTCondExpr::accept_value(Visitor *v)
{
	return v->visit_value(this);
}

Value *ASTCondExpr::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTCondExpr **********************************/

/*************************** ASTMathExpr *************************************/
ASTMathExpr::ASTMathExpr(ASTMathExpr *ltree, ASTMathExpr *rtree, Operation op)
{
	this->ltree = ltree;
	this->rtree = rtree;
	this->op = op;
}

ASTMathExpr::ASTMathExpr(ASTMathExpr *rtree, Operation op)
{
	this->ltree = nullptr;
	this->rtree = rtree;
	this->op = op;
}

ASTMathExpr::ASTMathExpr()
{
	return;
}

void ASTMathExpr::accept(Visitor *v)
{
	v->visit(this);
}

int ASTMathExpr::accept_value(Visitor *v)
{
	return v->visit_value(this);
}

Value *ASTMathExpr::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTMathExpr **********************************/

/*************************** ASTTargetVar ************************************/
ASTTargetVar::ASTTargetVar(string var_name, 
				ASTMathExpr *expr) : ASTMathExpr(expr, noop)
{
	this->var_name = var_name;
	array_type = true;
	isTarget = false;
}

ASTTargetVar::ASTTargetVar(string var_name)
{
	this->var_name = var_name;
	array_type = false;
	isTarget = false;
	setOp(noop);
}

ASTTargetVar::ASTTargetVar(string var_name, ASTMathExpr *expr, 
				Operation op) : ASTTargetVar(var_name, expr)
{
	setOp(op);
}

ASTTargetVar::ASTTargetVar(string var_name, 
				Operation op) : ASTTargetVar(var_name)
{
	setOp(op);
}

void ASTTargetVar::setOp(Operation op)
{
	this->op = op;
}

void ASTTargetVar::accept(Visitor *v)
{
	v->visit(this);
}

void ASTTargetVar::accept_value(Visitor *v, int value)
{
	v->visit_value(this, value);
}

int ASTTargetVar::accept_value(Visitor *v)
{
	return v->visit_value(this);
}

Value *ASTTargetVar::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTTargetVar *********************************/

/*************************** ASTWhileLoop ************************************/
ASTWhileLoop::ASTWhileLoop(ASTCondExpr *condition, ASTCodeBlock *statements)
{
	this->condition = condition;
	this->statements = statements;
}

void ASTWhileLoop::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTWhileLoop::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTWhileLoop *********************************/

/*************************** ASTForLoop **************************************/
ASTForLoop::ASTForLoop(ASTAssignment *assignment, ASTMathExpr *ulimit, 
						ASTMathExpr *increment, ASTCodeBlock *statements)
{
	this->assignment = assignment;
	this->ulimit = ulimit;
	this->increment = increment;
	this->statements = statements;
}

ASTForLoop::ASTForLoop(ASTAssignment *assignment, ASTMathExpr *ulimit,
						ASTCodeBlock *statements) : ASTForLoop(assignment,
											ulimit, nullptr, statements)
{}

void ASTForLoop::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTForLoop::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTForLoop ***********************************/

/*************************** ASTAssignment ***********************************/
ASTAssignment::ASTAssignment(ASTTargetVar *target, ASTMathExpr *rexpr)
{
	this->target = target;
	this->rexpr = rexpr;
}

void ASTAssignment::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTAssignment::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTAssignment ********************************/

/*************************** ASTCodeStatement ********************************/

void ASTCodeStatement::setLabel(string label)
{
	this->label = label;
}

void ASTCodeStatement::accept(Visitor *v)
{
	return;
}

/************************** End ASTCodeStatement *****************************/

/*************************** ASTCodeBlock ************************************/
ASTCodeBlock::ASTCodeBlock()
{
	return;
}

void ASTCodeBlock::addStatement(ASTCodeStatement *statement)
{
	statements.push_back(statement);
	statement->setParent(this);
}

void ASTCodeBlock::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTCodeBlock::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTCodeBlock *********************************/

/*************************** ASTVariable *************************************/
ASTVariable::ASTVariable(string var_name, bool array_type, unsigned int length)
{
	this->var_name = var_name;
	this->array_type = array_type;
	this->length = length;
}

ASTVariable::ASTVariable(string var_name, bool array_type)
{
	this->var_name = var_name;
	this->array_type = array_type;
}

void ASTVariable::setDataType(string data_type)
{
	this->data_type = data_type;
}

void ASTVariable::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTVariable::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTVariable **********************************/

/*************************** ASTVariableSet **********************************/

void ASTVariableSet::addVariable(ASTVariable *variable)
{
	variables.push_back(variable);
}

vector<ASTVariable *> ASTVariableSet::getVariables()
{
	return variables;
}

void ASTVariableSet::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTVariableSet::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTVariableSet *******************************/

/*************************** ASTDeclStatement ********************************/
ASTDeclStatement::ASTDeclStatement(string data_type, 
									ASTVariableSet *variableSet)
{
	this->variables = variableSet->getVariables();
	for(int i = 0; i < variables.size(); i++)
		variables[i]->setDataType(data_type);
}

void ASTDeclStatement::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTDeclStatement::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTDeclStatement *****************************/

/*************************** ASTDeclBlock ************************************/
ASTDeclBlock::ASTDeclBlock()
{
	return;
}

void ASTDeclBlock::addStatement(ASTDeclStatement *statement)
{
	statements.push_back(statement);
}

void ASTDeclBlock::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTDeclBlock::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/************************** End ASTDeclBlock *********************************/

/*************************** ASTProgram **************************************/

ASTProgram::ASTProgram(ASTDeclBlock *decl_block, ASTCodeBlock *code_block)
{
	this->decl_block = decl_block;
	this->code_block = code_block;
	if(decl_block)
		decl_block->setParent(this);
	if(code_block)
		code_block->setParent(this);
}

ASTProgram::ASTProgram(ASTDeclBlock *decl_block):
											ASTProgram(decl_block, nullptr)
{}

ASTProgram::ASTProgram(ASTCodeBlock *code_block):
											ASTProgram(nullptr, code_block)
{}

ASTProgram::ASTProgram(): ASTProgram(nullptr, nullptr)
{}

void ASTProgram::accept(Visitor *v)
{
	v->visit(this);
}

Value *ASTProgram::codegen(CodeGenVisitor *v)
{
	return v->visit(this);
}

/***************************End ASTProgram ***********************************/