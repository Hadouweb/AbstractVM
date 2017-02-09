#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP

#include <iostream>
#include <list>
#include <map>
#include "ParsedNode.class.hpp"
#include "Factory.class.hpp"
#include "Operand.class.hpp"

class VirtualMachine {
public:
    VirtualMachine(std::list<ParsedNode*> parsedList);

    virtual ~VirtualMachine(void);

    VirtualMachine & operator=(VirtualMachine const & rhs);
	static std::list<std::string> exceptionList;


private:
	VirtualMachine(void);
	VirtualMachine(VirtualMachine const & src);
	void executeInstr(std::list<ParsedNode*> parsedList);
	std::string getValueOnly(std::string str);
	enum eOperandType getEnumOperand(enum e_tk token);

	void execInstrPush(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrPop(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrDump(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrAssert(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrAdd(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrSub(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrMul(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrDiv(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrMod(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrPrint(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);
	void execInstrExit(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *> parsedList);

	typedef std::map<e_tk, void (VirtualMachine::*)(std::list<ParsedNode*>::iterator & it, std::list<ParsedNode *>) > execMapType;

	execMapType _execMap = {
		{TK_INSTR_PUSH, 	&VirtualMachine::execInstrPush},
		{TK_INSTR_POP, 		&VirtualMachine::execInstrPop},
		{TK_INSTR_DUMP, 	&VirtualMachine::execInstrDump},
		{TK_INSTR_ASSERT, 	&VirtualMachine::execInstrAssert},
		{TK_INSTR_ADD, 		&VirtualMachine::execInstrAdd},
		{TK_INSTR_SUB, 		&VirtualMachine::execInstrSub},
		{TK_INSTR_MUL, 		&VirtualMachine::execInstrMul},
		{TK_INSTR_DIV, 		&VirtualMachine::execInstrDiv},
		{TK_INSTR_MOD, 		&VirtualMachine::execInstrMod},
		{TK_INSTR_PRINT, 	&VirtualMachine::execInstrPrint},
		{TK_INSTR_EXIT, 	&VirtualMachine::execInstrExit},
	};

	Factory _factory;
	std::list<IOperand const *> _OpStack;
};

#endif