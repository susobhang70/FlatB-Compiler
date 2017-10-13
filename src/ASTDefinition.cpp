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

/*************************** ASTVisitor ****************************************/
ASTVisitor::ASTVisitor()
{
	return;
}

void ASTVisitor::visit(ASTCodeStatement *code_statement)
{
	return;
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
	if(program->decl_block)						// could be that there is no decl block
		program->decl_block->accept(this);
	if(program->code_block)						// could be that there is no code block
		program->code_block->accept(this);
	tabs--;
	xml << "</program>" << endl;
}

/************************** End ASTVisitor *************************************/

/*************************** ASTCodeStatement **********************************/
ASTCodeStatement::ASTCodeStatement()
{
	return;
}

void ASTCodeStatement::accept(Visitor *v)
{
	v->visit(this);
}

/************************** End ASTCodeStatement *******************************/

/*************************** ASTCodeBlock **************************************/
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

/************************** End ASTCodeBlock ***********************************/

/*************************** ASTVariable **************************************/
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

/************************** End ASTVariable ***********************************/

/*************************** ASTVariableSet ***********************************/

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

/************************** End ASTVariableSet ********************************/

/*************************** ASTDeclStatement *********************************/
ASTDeclStatement::ASTDeclStatement(string data_type, ASTVariableSet *variableSet)
{
	this->variables = variableSet->getVariables();
	for(int i = 0; i < variables.size(); i++)
		variables[i]->setDataType(data_type);
}

void ASTDeclStatement::accept(Visitor *v)
{
	v->visit(this);
}

/************************** End ASTDeclStatement ******************************/

/*************************** ASTDeclBlock *************************************/
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

/************************** End ASTDeclBlock **********************************/

/*************************** ASTProgram ***************************************/

ASTProgram::ASTProgram(ASTDeclBlock *decl_block, ASTCodeBlock *code_block)
{
	this->decl_block = decl_block;
	this->code_block = code_block;
}

void ASTProgram::accept(Visitor *v)
{
	v->visit(this);
}

/***************************End ASTProgram ************************************/