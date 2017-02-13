#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP

#include <iostream>
#include <list>
#include <map>
#include "ParsedNode.class.hpp"
#include "Factory.class.hpp"
#include "Operand.class.hpp"

class Factory;

class VirtualMachine {
public:
    VirtualMachine(std::list<ParsedNode*> parsedList);
	~VirtualMachine(void);

	void printOpStack(void) const;

private:
	VirtualMachine(void);
	VirtualMachine(VirtualMachine const & src);
	VirtualMachine & operator=(VirtualMachine const & rhs);
	void executeInstr(std::list<ParsedNode*> parsedList);
	std::string getValueOnly(std::string str);
	enum eOperandType getEnumOperand(enum e_tk token);

	void execInstrPush(std::list<ParsedNode*>::iterator & it);
	void execInstrPop(std::list<ParsedNode*>::iterator & it);
	void execInstrDump(std::list<ParsedNode*>::iterator & it);
	void execInstrAssert(std::list<ParsedNode*>::iterator & it);
	void execInstrAdd(std::list<ParsedNode*>::iterator & it);
	void execInstrSub(std::list<ParsedNode*>::iterator & it);
	void execInstrMul(std::list<ParsedNode*>::iterator & it);
	void execInstrDiv(std::list<ParsedNode*>::iterator & it);
	void execInstrMod(std::list<ParsedNode*>::iterator & it);
	void execInstrPrint(std::list<ParsedNode*>::iterator & it);
	void execInstrExit(std::list<ParsedNode*>::iterator & it);

	typedef std::map<e_tk, void (VirtualMachine::*)(std::list<ParsedNode*>::iterator & it) > execMapType;

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

	class AssertException : public std::exception {
		public:
			AssertException(void);
			~AssertException(void) throw();
			AssertException(AssertException const & src);
			virtual const char* what() const throw();
		private:
			AssertException & operator=(AssertException const & rhs);
	};

	class ValueExpectedException : public std::exception {
		public:
			ValueExpectedException(void);
			~ValueExpectedException(void) throw();
			ValueExpectedException(ValueExpectedException const & src);
			virtual const char* what() const throw();
		private:
			ValueExpectedException & operator=(ValueExpectedException const & rhs);
	};

	class ExitExpectedException : public std::exception {
		public:
			ExitExpectedException(void);
			~ExitExpectedException(void) throw();
			ExitExpectedException(ExitExpectedException const & src);
			virtual const char* what() const throw();
		private:
			ExitExpectedException & operator=(ExitExpectedException const & rhs);
	};

	std::list<IOperand const *> _OpStack;
};

#endif