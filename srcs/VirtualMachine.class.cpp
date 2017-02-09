#include "VirtualMachine.class.hpp"

VirtualMachine::VirtualMachine(void) {
	// TODO
}

VirtualMachine::VirtualMachine(VirtualMachine const &src) {
	*this = src;
}

VirtualMachine::~VirtualMachine(void) {
	// TODO
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

VirtualMachine::VirtualMachine(std::list<ParsedNode *> parsedList) {
	this->executeInstr(parsedList);
}

void VirtualMachine::executeInstr(std::list<ParsedNode *> parsedList) {
	for (std::list<ParsedNode*>::iterator it = parsedList.begin(); it != parsedList.end(); ++it) {
		execMapType::iterator it2 = this->_execMap.find((*it)->getTkInstr());
		if (it2 != this->_execMap.end()) {
			(this->*it2->second)(it, parsedList);
		} else
			std::cerr << "ERROR1" << std::endl;
	}
}

enum eOperandType VirtualMachine::getEnumOperand(enum e_tk token) {
	switch (token) {
		case TK_VALUE_INT_8:
			return INT_8;
		case TK_VALUE_INT_16:
			return INT_16;
		case TK_VALUE_INT_32:
			return INT_32;
		case TK_VALUE_FLOAT:
			return FLOAT;
		case TK_VALUE_DOUBLE:
			return DOUBLE;
		default:
			return NB_TYPE;
	}
}

std::string VirtualMachine::getValueOnly(std::string str) {
	unsigned first = str.find("(");
	unsigned last = str.find(")");
	std::string val = str.substr (first + 1, last - first - 1);
	return val;
}

void VirtualMachine::execInstrPush(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	std::string value = getValueOnly((*it)->getValue());
	const IOperand * op = this->_factory.createOperand(this->getEnumOperand((*it)->getTkValue()), value);

	this->_OpStack.push_front(op);

	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrPop(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrDump(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrAssert(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrAdd(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrSub(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrMul(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrDiv(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrMod(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrPrint(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

void VirtualMachine::execInstrExit(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (parsedList.size())
		;
	std::cout << "Exec: " << Node::convertEnumTk((*it)->getTkInstr()) << std::endl;
}

