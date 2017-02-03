#include "Node.class.hpp"

Node::Node(void) {
	// TODO
}

Node::Node(e_tk_instr tk, unsigned int numLine) : _token(tk), _numLine(numLine) {

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

std::string Node::convertEnumInstr(e_tk_instr e) {
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
	}
	return "NULL";
}

e_tk_instr Node::getToken(void) const {
	return this->_token;
}

unsigned int Node::getNumLine() const {
	return this->_numLine;
}

std::ostream &operator<<(std::ostream &os, Node &n) {
	os << Node::convertEnumInstr(n.getToken()) << " line : " << n.getNumLine() << std::endl;
	return os;
}
