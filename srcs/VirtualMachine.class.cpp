#include "VirtualMachine.class.hpp"

VirtualMachine::~VirtualMachine(void) {
	for(std::list<IOperand const *>::const_iterator it = this->_OpStack.begin(); it != this->_OpStack.end(); ++it) {
		delete *it;
	}
	this->_OpStack.clear();
}

VirtualMachine &VirtualMachine::operator=(VirtualMachine const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

VirtualMachine::VirtualMachine(std::list<ParsedNode *> parsedList) {
	try {
		this->executeInstr(parsedList);
	} catch(std::exception & e ) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

void VirtualMachine::executeInstr(std::list<ParsedNode *> parsedList) {
	for (std::list<ParsedNode*>::iterator it = parsedList.begin(); it != parsedList.end(); ++it) {
		execMapType::iterator it2 = this->_execMap.find((*it)->getTkInstr());
		if (it2 != this->_execMap.end()) {
			try {
				(this->*it2->second)(it);
			} catch (std::exception & e) {
				std::cerr << "Exception: " << e.what() << std::endl;
				exit(1);
			}
		}
	}
	throw VirtualMachine::ExitExpectedException();
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

void VirtualMachine::execInstrPush(std::list<ParsedNode *>::iterator &it) {
	std::string value = getValueOnly((*it)->getValue());
	const IOperand * op = Factory::getInstance()->createOperand(this->getEnumOperand((*it)->getTkValue()), value);

	this->_OpStack.push_front(op);
}

void VirtualMachine::execInstrPop(std::list<ParsedNode *>::iterator &it) {
	if (this->_OpStack.size() > 0) {
		IOperand const * opTop = *this->_OpStack.begin();
		this->_OpStack.pop_front();
		delete opTop;
	}
	else
		throw VirtualMachine::ValueExpectedException();
	if (*it)
		;
}

void VirtualMachine::execInstrDump(std::list<ParsedNode *>::iterator &it) {
	this->printOpStack();
	if (*it)
		;
}

void VirtualMachine::execInstrAssert(std::list<ParsedNode *>::iterator &it) {
	IOperand const * opTop = *this->_OpStack.begin();
	std::cout << "LOL" << std::endl;
	std::string value = getValueOnly((*it)->getValue());
	if (opTop && (opTop->toString().compare(value) != 0 || opTop->getType() != this->getEnumOperand((*it)->getTkValue())))
		throw VirtualMachine::AssertException();
	if (*it)
		;
}

void VirtualMachine::execInstrAdd(std::list<ParsedNode *>::iterator &it) {
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
	delete opTop1;
	delete opTop2;
	if (*it)
		;
}

void VirtualMachine::execInstrSub(std::list<ParsedNode *>::iterator &it) {
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
	delete opTop1;
	delete opTop2;
	if (*it)
		;
}

void VirtualMachine::execInstrMul(std::list<ParsedNode *>::iterator &it) {
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
	delete opTop1;
	delete opTop2;
	if (*it)
		;
}

void VirtualMachine::execInstrDiv(std::list<ParsedNode *>::iterator &it) {
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
	delete opTop1;
	delete opTop2;
	if (*it)
		;
}

void VirtualMachine::execInstrMod(std::list<ParsedNode *>::iterator &it) {
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
	delete opTop1;
	delete opTop2;
	if (*it)
		;
}

void VirtualMachine::execInstrPrint(std::list<ParsedNode *>::iterator &it) {
	IOperand const * opTop = *this->_OpStack.begin();
	if (opTop == NULL)
		throw VirtualMachine::ValueExpectedException();
	if (opTop->getType() == INT_8) {
		char c = std::stoi(opTop->toString());
		std::cout << c;
	} else
		throw VirtualMachine::AssertException();
	if (*it)
		;
}

void VirtualMachine::execInstrExit(std::list<ParsedNode *>::iterator &it) {
	exit(0);
	if (*it)
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

VirtualMachine::ExitExpectedException::ExitExpectedException(void) { }

VirtualMachine::ExitExpectedException::ExitExpectedException(const VirtualMachine::ExitExpectedException &src) {
	*this = src;
}

VirtualMachine::ExitExpectedException::~ExitExpectedException(void) throw() { }

VirtualMachine::ExitExpectedException & VirtualMachine::ExitExpectedException::operator=(const VirtualMachine::ExitExpectedException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *VirtualMachine::ExitExpectedException::what() const throw() {
	return "Exception: exit instruction is expected at the end";
}