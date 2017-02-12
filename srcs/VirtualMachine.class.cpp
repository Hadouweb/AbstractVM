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
			try {
				(this->*it2->second)(it, parsedList);
			} catch (std::exception & e) {
				std::cerr << "Exception: " << e.what() << std::endl;
				exit(1);
			}
		}
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
}

void VirtualMachine::execInstrPop(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	if (this->_OpStack.size() > 0)
		this->_OpStack.pop_front();
	else
		throw VirtualMachine::ValueExpectedException();
	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrDump(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {

	this->printOpStack();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrAssert(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop = *this->_OpStack.begin();
	std::string value = getValueOnly((*it)->getValue());
	if (opTop->toString().compare(value) != 0 || opTop->getType() != this->getEnumOperand((*it)->getTkValue()))
		throw VirtualMachine::AssertException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrAdd(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop1 = *this->_OpStack.begin();
	if (opTop1)
		this->_OpStack.pop_front();
	IOperand const * opTop2 = *this->_OpStack.begin();
	if (opTop2)
		this->_OpStack.pop_front();

	if (opTop1 && opTop2) {
		IOperand const * op = *opTop1 + *opTop2;
		this->_OpStack.push_front(op);
	} else
		throw VirtualMachine::ValueExpectedException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrSub(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop1 = *this->_OpStack.begin();
	if (opTop1)
		this->_OpStack.pop_front();
	IOperand const * opTop2 = *this->_OpStack.begin();
	if (opTop2)
		this->_OpStack.pop_front();

	if (opTop1 && opTop2) {
		IOperand const * op = *opTop1 - *opTop2;
		this->_OpStack.push_front(op);
	} else
		throw VirtualMachine::ValueExpectedException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrMul(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop1 = *this->_OpStack.begin();
	if (opTop1)
		this->_OpStack.pop_front();
	IOperand const * opTop2 = *this->_OpStack.begin();
	if (opTop2)
		this->_OpStack.pop_front();

	if (opTop1 && opTop2) {
		IOperand const * op = *opTop1 * *opTop2;
		this->_OpStack.push_front(op);
	} else
		throw VirtualMachine::ValueExpectedException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrDiv(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop1 = *this->_OpStack.begin();
	if (opTop1)
		this->_OpStack.pop_front();
	IOperand const * opTop2 = *this->_OpStack.begin();
	if (opTop2)
		this->_OpStack.pop_front();

	if (opTop1 && opTop2) {
		IOperand const * op = *opTop1 / *opTop2;
		this->_OpStack.push_front(op);
	} else
		throw VirtualMachine::ValueExpectedException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrMod(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop1 = *this->_OpStack.begin();
	if (opTop1)
		this->_OpStack.pop_front();
	IOperand const * opTop2 = *this->_OpStack.begin();
	if (opTop2)
		this->_OpStack.pop_front();

	if (opTop1 && opTop2) {
		IOperand const * op = *opTop1 % *opTop2;
		this->_OpStack.push_front(op);
	} else
		throw VirtualMachine::ValueExpectedException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrPrint(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	IOperand const * opTop = *this->_OpStack.begin();

	if (opTop->getType() == INT_8) {
		char c = std::stoi(opTop->toString());
		std::cout << c;
	} else
		throw VirtualMachine::AssertException();

	if (parsedList.size() && *it)
		;
}

void VirtualMachine::execInstrExit(std::list<ParsedNode *>::iterator &it, std::list<ParsedNode *> parsedList) {
	exit(0);
	if (parsedList.size() && *it)
		;
}

void VirtualMachine::printOpStack(void) const {
	for(std::list<IOperand const *>::const_iterator it = this->_OpStack.begin(); it != this->_OpStack.end(); ++it) {
		std::cout << (*it)->toString() << std::endl;
	}
}

VirtualMachine::AssertException::AssertException(void) { }

VirtualMachine::AssertException::~AssertException(void) throw() { }

const char *VirtualMachine::AssertException::what() const throw() {
	return "Value is not correct";
}

VirtualMachine::AssertException::AssertException(const VirtualMachine::AssertException &src) {
	*this = src;
}

VirtualMachine::AssertException &VirtualMachine::AssertException::operator=(
		const VirtualMachine::AssertException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

VirtualMachine::ValueExpectedException::ValueExpectedException(void) { }

VirtualMachine::ValueExpectedException::~ValueExpectedException(void) throw() { }

VirtualMachine::ValueExpectedException::ValueExpectedException(
		const VirtualMachine::ValueExpectedException &src) {
	*this = src;
}

const char *VirtualMachine::ValueExpectedException::what() const throw() {
	return "At least one value is missing";
}

VirtualMachine::ValueExpectedException &
VirtualMachine::ValueExpectedException::operator=(
		const VirtualMachine::ValueExpectedException &rhs) {
	if (this != &rhs){
	}
	return *this;
}
