#include "Node.class.hpp"

Node::Node(void) { }

Node::Node(e_tk tk, std::string val, unsigned int numLine, unsigned int numCol)
	: _token(tk), _value(val), _numLine(numLine), _numCol(numCol) {

}

Node::Node(Node const &src) {
	*this = src;
}

Node::~Node(void) { }

Node &Node::operator=(Node const &rhs) {
	if (this != &rhs) {
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
		case TK_COMMENT:
			return "TK_COMMENT";
		case TK_END_LINE:
			return "TK_END_LINE";
		case TK_WHITE_SPACE:
			return "TK_WHITE_SPACE";
		case TK_DSEMI_COL:
			return "TK_DSEMI_COL";
		case NB_TK:
			return "NB_TK";
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

std::ostream &operator<<(std::ostream &os, Node &n) {
	os << Node::convertEnumTk(n.getToken()) << " |" << n.getValue() << "| col : " << n.getNumCol() << " line : " << n.getNumLine() << std::endl;
	return os;
}
