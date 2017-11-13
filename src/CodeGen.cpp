#include "ASTDefinition.h"
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <cstdio>
#include <fcntl.h>
#include <stack>
#include <map>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/Bitcode/ReaderWriter.h"

using namespace std;
using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;

Type* IntType()
{
	return Type::getInt64Ty(TheModule->getContext());
}

Value* CodeGenVisitor::checkLabel(ASTCodeStatement *statement)
{
	if(!statement->label.empty())
	{
		BasicBlock *newLabelBlock;
		if(labels.find(statement->label) == labels.end())
		{
			newLabelBlock = BasicBlock::Create(TheContext, statement->label, currentBlock()->getParent());
			labels[statement->label] = newLabelBlock;
		}
		else
		{
			newLabelBlock = labels[statement->label];
		}

		BranchInst::Create(newLabelBlock, currentBlock());
		popBlock();
		pushBlock(newLabelBlock);
	}
}

void CodeGenVisitor::generateCode(ASTProgram *program)
{
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(TheContext), false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", TheModule.get());
	BasicBlock *bblock = BasicBlock::Create(TheContext, "entry", mainFunction, 0);

	FunctionType *ptype = FunctionType::get(IntegerType::getInt32Ty(TheContext), PointerType::get(Type::getInt8Ty(TheContext), 0), true );
	Print = dynamic_cast<Function *>(TheModule->getOrInsertFunction("printf", ptype));
	Scan = dynamic_cast<Function *>(TheModule->getOrInsertFunction("scanf", ptype));

	// Push a new variable/block context
	pushBlock(bblock);
	
	program->codegen(this);

	if(errors > 0)
		exit(1);

	bblock = currentBlock();
	popBlock();
	ReturnInst::Create(TheContext, bblock);

	verifyModule(*TheModule);

	cout << "LLVM IR Code" << endl;
	cout << "--------------------------------" << endl;
	cout << endl;

	legacy::PassManager PM;
	PM.add(createPrintModulePass(outs()));
	PM.run(*TheModule);

	// int fileDescriptor = open ("IRCode", O_RDWR|O_CREAT, 0777);
	// raw_fd_ostream OS(fileDescriptor, true);
	// WriteBitcodeToFile(TheModule.get(), OS);
	// OS.flush();
}

CodeGenVisitor::CodeGenVisitor(map<string, SymbolTableEntry *> st)
{
	TheModule = make_unique<Module>("main", TheContext);
	symboltable = st;
	errors = 0;
}

Value* CodeGenVisitor::visit(ASTIOBlock *ioblock)
{
	if(ioblock->iostmt == readvar)
	{
		std::vector<Value *> ArgsV;
		ArrayType* arrayType = nullptr;
		Value *val = ioblock->expr->codegen(this);

		ioblock->output += "%d";

		if(!ioblock->output.empty())
		{
			const char *str = ioblock->output.c_str();

			Constant *StrConstant = ConstantDataArray::getString(TheContext, str);
			GlobalVariable *gv = new GlobalVariable(*TheModule, StrConstant->getType(),
									true, GlobalValue::PrivateLinkage, StrConstant, "", nullptr,
									GlobalVariable::NotThreadLocal, 0);
			gv->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);

			Value *zero = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
			Value *Args[] = { zero, zero };
			Value *V = Builder.CreateInBoundsGEP(gv->getValueType(), gv, Args, "");

			ArgsV.push_back(V);
			if(ioblock->expr)
				ArgsV.push_back(val);

			if(Scan)
				CallInst::Create(Scan, ArgsV, "scanfCall", currentBlock());
		}
		return nullptr;
	}
	else
	{
		std::vector<Value *> ArgsV;
		ArrayType* arrayType = nullptr;
		Value *val = nullptr;

		if(ioblock->expr)
		{
			val = ioblock->expr->codegen(this);
			ioblock->output += "%d";
		}

		if(ioblock->iostmt == println)
			ioblock->output += "\n";

		if(!ioblock->output.empty())
		{
			const char *str = ioblock->output.c_str();

			Constant *StrConstant = ConstantDataArray::getString(TheContext, str);
			GlobalVariable *gv = new GlobalVariable(*TheModule, StrConstant->getType(),
									true, GlobalValue::PrivateLinkage, StrConstant, "", nullptr,
									GlobalVariable::NotThreadLocal, 0);
			gv->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);

			Value *zero = ConstantInt::get(Type::getInt32Ty(TheContext), 0);
			Value *Args[] = { zero, zero };
			Value *V = Builder.CreateInBoundsGEP(gv->getValueType(), gv, Args, "");

			ArgsV.push_back(V);
			if(ioblock->expr)
				ArgsV.push_back(val);

			if(Print)
				CallInst::Create(Print, ArgsV, "printfcall", currentBlock());
		}
		return nullptr;
	}
}

Value* CodeGenVisitor::visit(ASTGotoBlock *gotoblock)
{
	checkLabel(gotoblock);
	if(gotoblock->condition)
	{
		Value *condition = gotoblock->condition->codegen(this);
		ICmpInst *comparison = new ICmpInst(*currentBlock(), ICmpInst::ICMP_NE, condition, ConstantInt::get(IntType(), 0, true), "tmp");

		if(symboltable.find(gotoblock->targetlabel) != symboltable.end())
		{
			BasicBlock *jumpBlock;
			if(labels.find(gotoblock->targetlabel) != labels.end())
			{
				jumpBlock = labels[gotoblock->targetlabel];
			}
			else
			{
				jumpBlock = BasicBlock::Create(TheContext, gotoblock->targetlabel, currentBlock()->getParent());
				labels[gotoblock->targetlabel] = jumpBlock;
			}

			BasicBlock *noJumpBlock = BasicBlock::Create(TheContext, "noJumpBlock", currentBlock()->getParent());
			BranchInst::Create(jumpBlock, noJumpBlock, comparison, currentBlock());
			popBlock();
			pushBlock(noJumpBlock);
		}
	}
	else
	{
		if(symboltable.find(gotoblock->targetlabel) != symboltable.end())
		{
			BasicBlock *jumpBlock;
			if(labels.find(gotoblock->targetlabel) != labels.end())
			{
				jumpBlock = labels[gotoblock->targetlabel];
				BranchInst::Create(jumpBlock, currentBlock());
			}
			else
			{
				jumpBlock = BasicBlock::Create(TheContext, gotoblock->targetlabel, currentBlock()->getParent());
				labels[gotoblock->targetlabel] = jumpBlock;

				BasicBlock *noJumpBlock = BasicBlock::Create(TheContext, "noJumpBlock", currentBlock()->getParent());
				BranchInst::Create(jumpBlock, currentBlock());
				// BranchInst::Create(noJumpBlock, currentBlock());
				popBlock();
				pushBlock(noJumpBlock);
			}
			// BranchInst::Create(jumpBlock, currentBlock());
		}
	}
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTIfElse *ifelse)
{
	checkLabel(ifelse);
	BasicBlock *entryBlock = currentBlock();
	Value *condition = ifelse->condition->codegen(this);
	ICmpInst * comparison = new ICmpInst(*entryBlock, ICmpInst::ICMP_NE, condition, ConstantInt::get(IntType(), 0, true), "tmp");
	BasicBlock *ifBlock = BasicBlock::Create(TheContext, "ifBlock", entryBlock->getParent());
	BasicBlock *mergeBlock = BasicBlock::Create(TheContext, "mergeBlock", entryBlock->getParent());

	BasicBlock * returnedBlock = nullptr;

	pushBlock(ifBlock);
	ifelse->iftrue->codegen(this);
	returnedBlock = currentBlock();
	popBlock();

	if (!returnedBlock->getTerminator())
	{
		BranchInst::Create(mergeBlock, returnedBlock);
	}

	if (ifelse->iffalse)
	{
		BasicBlock *elseBlock = BasicBlock::Create(TheContext, "elseBlock", entryBlock->getParent());

		pushBlock(elseBlock);
		ifelse->iffalse->codegen(this);
		returnedBlock = currentBlock();
		popBlock();

		if (!returnedBlock->getTerminator())
		{
			BranchInst::Create(mergeBlock, returnedBlock);
		}

		BranchInst::Create(ifBlock, elseBlock, comparison, entryBlock);
	}
	else
	{
		BranchInst::Create(ifBlock, mergeBlock, comparison, entryBlock);
	}

	popBlock();
	pushBlock(mergeBlock);
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTCondExpr *condition)
{
	Value *lval = static_cast<Value*>(condition->ltree->codegen(this));
	Value *rval = static_cast<Value*>(condition->rtree->codegen(this));

	Value *outcome = nullptr;
	switch(condition->condition)
	{
		case les: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SLT, lval, rval,"tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
		case grt: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SGT, lval, rval, "tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
		case leq: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SLE, lval, rval, "tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
		case geq: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_SGE, lval, rval, "tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
		case neq: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lval, rval, "tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
		case eqto: 
			outcome = new ZExtInst(ICmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lval, rval, "tmp", currentBlock()), IntType(), "zext", currentBlock());
			break;
	}

	// if(condition->unot)
	// 	return new ZExtInst(CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, ConstantInt::get(IntType(), 0, true), outcome,"tmp", currentBlock()), IntType(), "zext", currentBlock());

	return outcome;
}

Value* CodeGenVisitor::visit(ASTForLoop *forloop)
{
	checkLabel(forloop);

	BasicBlock *entryBlock = currentBlock();
	BasicBlock *headerBlock = BasicBlock::Create(TheContext, "loop_header", entryBlock->getParent(), 0);
	BasicBlock *bodyBlock = BasicBlock::Create(TheContext, "loop_body", entryBlock->getParent(), 0);
	BasicBlock *afterLoopBlock = BasicBlock::Create(TheContext, "after_loop", entryBlock->getParent(), 0);

	// put the increment in the body block
	ASTTargetVar *iterator = new ASTTargetVar(forloop->assignment->target->var_name);
	iterator->setTarget();
	ASTAssignment* increment = new ASTAssignment(iterator, new ASTMathExpr(new ASTTargetVar(forloop->assignment->target->var_name), new ASTInteger(1), add));
	forloop->statements->addStatement(increment);

	forloop->assignment->codegen(this);

	Value *endVal = forloop->ulimit->codegen(this);

	Value *val = new LoadInst(variables[forloop->assignment->target->var_name], "load", headerBlock);
	ICmpInst *comparison = new ICmpInst(*headerBlock, ICmpInst::ICMP_SLT, val, endVal, "tmp");

	BranchInst::Create(bodyBlock, afterLoopBlock, comparison, headerBlock);
	BranchInst::Create(headerBlock, entryBlock);

	pushBlock(bodyBlock);
	forloop->statements->codegen(this);
	bodyBlock = currentBlock();

	popBlock();

	if (!bodyBlock->getTerminator())
	{
		BranchInst::Create(headerBlock, bodyBlock);
	}

	popBlock();
	pushBlock(afterLoopBlock);

	return nullptr;
}

Value* CodeGenVisitor::visit(ASTWhileLoop *whileloop)
{
	// TO-DO

	checkLabel(whileloop);

	BasicBlock *entryBlock = currentBlock();
	BasicBlock *headerBlock = BasicBlock::Create(TheContext, "loop_header", entryBlock->getParent(), 0);
	BasicBlock *bodyBlock = BasicBlock::Create(TheContext, "loop_body", entryBlock->getParent(), 0);
	BasicBlock *afterLoopBlock = BasicBlock::Create(TheContext, "after_loop", entryBlock->getParent(), 0);

	pushBlock(headerBlock);
	Value* val = whileloop->condition->codegen(this);
	ICmpInst *comparison = new ICmpInst(*headerBlock, ICmpInst::ICMP_NE, val, ConstantInt::get(IntType(), 0, true), "tmp");
	popBlock();

	BranchInst::Create(bodyBlock, afterLoopBlock, comparison, headerBlock);
	BranchInst::Create(headerBlock, entryBlock);

	pushBlock(bodyBlock);
	whileloop->statements->codegen(this);
	bodyBlock = currentBlock();

	popBlock();

	if (!bodyBlock->getTerminator())
	{
		BranchInst::Create(headerBlock, bodyBlock);
	}

	popBlock();
	pushBlock(afterLoopBlock);

	return nullptr;
}

Value* CodeGenVisitor::visit(ASTMathExpr *mathexpr)
{
	Value *lval = nullptr;
	Value *rval = nullptr;

	if(mathexpr->ltree)
		lval = mathexpr->ltree->codegen(this);

	if(mathexpr->rtree)
		rval = mathexpr->rtree->codegen(this);

	switch(mathexpr->op)
	{
		case add:
			return BinaryOperator::Create(Instruction::Add, lval, rval, "tmp", currentBlock());
		case sub:
			return BinaryOperator::Create(Instruction::Sub, lval, rval, "tmp", currentBlock());
		case mult:
			return BinaryOperator::Create(Instruction::Mul, lval, rval, "tmp", currentBlock());
		case divd:
			return BinaryOperator::Create(Instruction::SDiv, lval, rval, "tmp", currentBlock());
		case usub:
			lval = ConstantInt::get(IntType(), -1, true);
			return BinaryOperator::Create(Instruction::SDiv, lval, rval, "tmp", currentBlock());
		case noop:
			return rval;

	}
}

Value* CodeGenVisitor::visit(ASTInteger *integer)
{
	return ConstantInt::get(IntType(), integer->lexval, true);
}

Value* CodeGenVisitor::visit(ASTTargetVar *var_location)
{
	if(variables.find(var_location->var_name) != variables.end())
	{
		Value* location = nullptr;

		if(var_location->array_type)
		{
			if(!symboltable[var_location->var_name]->isArray)
			{
				errors++;
				cerr << "[ERROR] " << var_location->var_name << " not an array" << endl;
				return nullptr;
			}

			vector<Value *> index;
			index.push_back(ConstantInt::get(IntType(), 0, true));
			index.push_back(var_location->rtree->codegen(this));
			Value *val = variables[var_location->var_name];
			location = GetElementPtrInst::CreateInBounds(val, index, "tmp", currentBlock());
		}
		else
		{
			if(symboltable[var_location->var_name]->isArray)
			{
				errors++;
				cerr << "[ERROR] " << var_location->var_name << " is an array" << endl;
				return nullptr;
			}

			location = variables[var_location->var_name];
		}
		if(!var_location->isTarget)
			return new LoadInst(location, "", false, currentBlock());
		else
			return location;
	}
	else
	{
		errors++;
		cerr << var_location->var_name << " referenced before declaration" << endl;
		return nullptr;
	}
}

Value* CodeGenVisitor::visit(ASTAssignment *assignment)
{
	if(variables.find(assignment->target->var_name) != variables.end())
	{		
		checkLabel(assignment);

		Value* location = assignment->target->codegen(this);
		Value* expr = assignment->rexpr->codegen(this);

		if(location)
		{
			return new StoreInst(expr, location, false, currentBlock());
		}
		else
			return nullptr;
	}
	else
	{
		errors++;
		cerr << assignment->target->var_name << " referenced before declaration" << endl;
		return nullptr;
	}
}

Value* CodeGenVisitor::visit(ASTCodeBlock *code_block)
{
	for(auto statement: code_block->statements)
	{
		Value *V = statement->codegen(this);
	}
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTVariable *variable)
{
	// This is just in case. We have already checked all this in first run through, while
	// creation of symbol table
	if(this->variables.find(variable->var_name) != this->variables.end())
	{
		errors++;
		cerr << "[ERROR] Multiple variable declarations of " << variable->var_name << endl;
		return nullptr;
	}

	GlobalVariable *globalVar;

	if(variable->array_type)
	{
		if(variable->length < 1)
		{
			errors++;
			cerr << "[ERROR] Invalid Array Size for " << variable->var_name << endl;
			return nullptr;
		}

		ArrayType* arrayType = ArrayType::get(IntType(), variable->length);

		globalVar = new GlobalVariable(*TheModule, arrayType, false, GlobalValue::CommonLinkage, NULL, variable->var_name);
		globalVar->setInitializer(ConstantAggregateZero::get(arrayType));
	}
	else
	{
		globalVar = new GlobalVariable(*TheModule, IntType(), false, GlobalValue::CommonLinkage, NULL, variable->var_name);
		globalVar->setInitializer(ConstantInt::get(Type::getInt64Ty(TheContext), 0, true));
	}

	this->variables[variable->var_name] = globalVar;
	return globalVar;
}

Value* CodeGenVisitor::visit(ASTVariableSet *variableSet)
{
	for(auto variable: variableSet->variables)
	{
		Value *V = variable->codegen(this);
	}
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTDeclStatement *decl_line)
{
	for(auto variable: decl_line->variables)
	{
		Value *V = variable->codegen(this);
	}
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTDeclBlock *decl_block)
{
	for(auto statement: decl_block->statements)
	{
		Value *V = statement->codegen(this);
	}
	return nullptr;
}

Value* CodeGenVisitor::visit(ASTProgram *program)
{
	if(program->decl_block)
	{
		Value *V = program->decl_block->codegen(this);
	}

	if(program->code_block)
	{
		Value *V = program->code_block->codegen(this);
	}

	return nullptr;
}
