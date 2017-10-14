#include "ASTDefinition.h"
#include <iostream>
#include <fstream>

using namespace std;

ofstream xml("AST_XML.xml");
int tabs = 0;

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

/*************************** ASTVisitor **************************************/
ASTVisitor::ASTVisitor()
{
	return;
}

void ASTVisitor::printLabel(ASTCodeStatement *statement)
{
	if(!statement->label.empty())
	{
		insertTabs();
		xml << "<label name=\'" << statement->label << "\' />" << endl;
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
	insertTabs();
	xml << "<variable name=\'" << variable->var_name << "\' ";
	if(variable->array_type)
		xml << "size=\'" << variable->length << "\' ";
	xml << "type=\'" << variable->data_type << "\' />" << endl;
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

/************************** End ASTVisitor ***********************************/

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

/************************** End ASTGotoBlock *********************************/

/*************************** ASTIfElse ***************************************/
ASTIfElse::ASTIfElse(ASTCondExpr *condition, ASTNode *iftrue, ASTNode *iffalse)
{
	this->condition = condition;
	this->iftrue = iftrue;
	this->iffalse = iffalse;
}

ASTIfElse::ASTIfElse(ASTCondExpr *condition, ASTNode *iftrue):
										ASTIfElse(condition, iftrue, nullptr)
{}

void ASTIfElse::accept(Visitor *v)
{
	v->visit(this);
}

/************************** End ASTIfElse ************************************/

/*************************** ASTInteger **************************************/

ASTInteger::ASTInteger(int lexval)
{
	this->lexval = lexval;
}

void ASTInteger::accept(Visitor *v)
{
	v->visit(this);
}

/************************** End ASTInteger ***********************************/

/*************************** ASTCondExpr *************************************/
ASTCondExpr::ASTCondExpr(ASTNode *ltree, Condition condition, ASTNode *rtree)
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

/************************** End ASTCondExpr **********************************/

/*************************** ASTMathExpr *************************************/
ASTMathExpr::ASTMathExpr(ASTNode *ltree, ASTNode *rtree, Operation op)
{
	this->ltree = ltree;
	this->rtree = rtree;
	this->op = op;
}

ASTMathExpr::ASTMathExpr(ASTNode *rtree, Operation op)
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

/************************** End ASTMathExpr **********************************/

/*************************** ASTTargetVar ************************************/
ASTTargetVar::ASTTargetVar(string var_name, 
				ASTNode *expr) : ASTMathExpr(expr, noop)
{
	this->var_name = var_name;
	array_type = true;
}

ASTTargetVar::ASTTargetVar(string var_name)
{
	this->var_name = var_name;
	array_type = false;
	setOp(noop);
}

ASTTargetVar::ASTTargetVar(string var_name, ASTNode *expr, 
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

/************************** End ASTForLoop ***********************************/

/*************************** ASTAssignment ***********************************/
ASTAssignment::ASTAssignment(ASTTargetVar *target, ASTNode *rexpr)
{
	this->target = target;
	this->rexpr = rexpr;
}

void ASTAssignment::accept(Visitor *v)
{
	v->visit(this);
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
}

void ASTCodeBlock::accept(Visitor *v)
{
	v->visit(this);
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

/************************** End ASTDeclBlock *********************************/

/*************************** ASTProgram **************************************/

ASTProgram::ASTProgram(ASTDeclBlock *decl_block, ASTCodeBlock *code_block)
{
	this->decl_block = decl_block;
	this->code_block = code_block;
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

/***************************End ASTProgram ***********************************/