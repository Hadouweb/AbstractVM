#include "Node.class.hpp"

Node::Node(void) {
	// TODO
}

Node::Node(e_tk tk, unsigned int numLine) : _token(tk), _numLine(numLine) {

}

Node::Node(Node const &src) {
	*this = src;
}

Node::~Node(void) {
	// TODO
}

Node &Node::operator=(Node const &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

std::string Node::convertEnumTk(e_tk e) {
	switch (e) {
		case TK_INSTR_PUSH:
			return "TK_INSTR_PUSH";
		case TK_INSTR_POP:
			return "TK_INSTR_POP";
		case TK_INSTR_DUMP:
			return "TK_INSTR_DUMP";
		case TK_INSTR_ASSERT:
			return "TK_INSTR_ASSERT";
		case TK_INSTR_ADD:
			return "TK_INSTR_ADD";
		case TK_INSTR_SUB:
			return "TK_INSTR_SUB";
		case TK_INSTR_MUL:
			return "TK_INSTR_MUL";
		case TK_INSTR_DIV:
			return "TK_INSTR_DIV";
		case TK_INSTR_MOD:
			return "TK_INSTR_MOD";
		case TK_INSTR_PRINT:
			return "TK_INSTR_PRINT";
		case TK_INSTR_EXIT:
			return "TK_INSTR_EXIT";
		case TK_COMMENT:
			return "TK_COMMENT";
		case TK_UNKNOWN:
			return "TK_UNKNOWN";
		case TK_VALUE_INT_8:
			return "TK_VALUE_INT_8";
		case TK_VALUE_INT_16:
			return "TK_VALUE_INT_16";
		case TK_VALUE_INT_32:
			return "TK_VALUE_INT_32";
		case TK_VALUE_FLOAT:
			return "TK_VALUE_FLOAT";
		case TK_VALUE_DOUBLE:
			return "TK_VALUE_DOUBLE";
	}
	return "NULL";
}

e_tk Node::getToken(void) const {
	return this->_token;
}

unsigned int Node::getNumLine() const {
	return this->_numLine;
}

int8_t Node::getValueInt8() const {
	return this->_valueInt8;
}

int16_t Node::getValueInt16() const {
	return this->_valueInt16;
}

int32_t Node::getValueInt32() const {
	return this->_valueInt32;
}

float Node::getValueFloat() const {
	return this->_valueFloat;
}

double Node::getValueDouble() const {
	return this->_valueDouble;
}

void Node::setValueDouble(double _valueDouble) {
	this->_valueDouble = _valueDouble;
}

void Node::setValueFloat(float _valueFloat) {
	this->_valueFloat = _valueFloat;
}

void Node::setValueInt32(int32_t _valueInt32) {
	this->_valueInt32 = _valueInt32;
}

void Node::setValueInt16(int16_t _valueInt16) {
	this->_valueInt16 = _valueInt16;
}

void Node::setValueInt8(int8_t _valueInt8) {
	this->_valueInt8 = _valueInt8;
}

std::ostream &operator<<(std::ostream &os, Node &n) {
	if (n.getToken() == TK_VALUE_INT_8)
		os << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValueInt8() << "] line : " << n.getNumLine() << std::endl;
	else if (n.getToken() == TK_VALUE_INT_16)
		os << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValueInt16() << "] line : " << n.getNumLine() << std::endl;
	else if (n.getToken() == TK_VALUE_INT_32)
		os << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValueInt32() << "] line : " << n.getNumLine() << std::endl;
	else if (n.getToken() == TK_VALUE_FLOAT)
		os << std::fixed << std::setprecision(4) << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValueFloat() << "] line : " << n.getNumLine() << std::endl;
	else if (n.getToken() == TK_VALUE_DOUBLE)
		os << std::fixed << std::setprecision(4) << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValueDouble() << "] line : " << n.getNumLine() << std::endl;
	else
		os << Node::convertEnumTk(n.getToken()) << " line : " << n.getNumLine() << std::endl;
	return os;
}
