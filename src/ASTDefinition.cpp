#include "ASTDefinition.h"

using namespace std;

/*************************** ASTCodeBlock **************************************/
ASTCodeBlock::ASTCodeBlock()
{
	return;
}

void ASTCodeBlock::accept(Visitor *v)
{
	v->visit(this);
}

/************************** End ASTCodeBlock ***********************************/

/*************************** ASTVariable **************************************/
ASTVariable::ASTVariable(string var_name, bool array_type, int length)
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