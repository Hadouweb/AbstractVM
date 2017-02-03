#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

#include "Lexer.class.hpp"

enum e_tk_instr {
	TK_INSTR_PUSH,
	TK_INSTR_POP,
	TK_INSTR_DUMP,
	TK_INSTR_ASSERT,
	TK_INSTR_ADD,
	TK_INSTR_SUB,
	TK_INSTR_MUL,
	TK_INSTR_DIV,
	TK_INSTR_MOD,
	TK_INSTR_PRINT,
	TK_INSTR_EXIT,
	TK_COMMENT,
	TK_UNKNOWN,
};

enum e_tk_value {
	TK_VALUE_INT_8,
	TK_VALUE_INT_16,
	TK_VALUE_INT_32,
	TK_VALUE_FLOAT,
	TK_VALUE_DOUBLE,
};

class Node {
public:
	Node(e_tk_instr tk, unsigned int numLine);
    Node(Node const & src);

    ~Node(void);

    Node & operator=(Node const & rhs);
    e_tk_instr getToken(void) const;
    unsigned int getNumLine() const;
	static std::string convertEnumInstr(e_tk_instr e);

private:
	Node(void);
	e_tk_instr _token;
	unsigned int _numLine;
};

std::ostream & operator<<(std::ostream & os, Node & n);

#endif