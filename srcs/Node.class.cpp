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

unsigned int Node::getNumCol() const {
	return this->_numCol;
}

std::string Node::getValue() const {
	return this->_value;
}

void Node::setValue(std::string v) {
	this->_value = v;
}

std::string Node::getComment() const {
	return this->_comment;
}

void Node::setComment(std::string comment) {
	this->_comment = comment;
}

std::ostream &operator<<(std::ostream &os, Node &n) {
	if (n.getToken() == TK_COMMENT)
		os << Node::convertEnumTk(n.getToken()) << " val : [" << n.getComment() << "] col : " << n.getNumCol() << " line : " << n.getNumLine() << std::endl;
	else if (n.getToken() == TK_VALUE_INT_8 ||
			n.getToken() == TK_VALUE_INT_16 ||
			n.getToken() == TK_VALUE_INT_32 ||
			n.getToken() == TK_VALUE_FLOAT ||
			n.getToken() == TK_VALUE_DOUBLE)
		os << std::fixed << std::setprecision(4) << Node::convertEnumTk(n.getToken()) << " val : [" << n.getValue() << "] col : " << n.getNumCol() << " line : " << n.getNumLine() << std::endl;
	else
		os << Node::convertEnumTk(n.getToken()) << " col : " << n.getNumCol() << " line : " << n.getNumLine() << std::endl;
	return os;
}
