#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

#include "Lexer.class.hpp"
#include <iomanip>

enum e_tk {
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
	TK_VALUE_INT_8,
	TK_VALUE_INT_16,
	TK_VALUE_INT_32,
	TK_VALUE_FLOAT,
	TK_VALUE_DOUBLE,
	TK_UNKNOWN,
};

class Node {
public:
	Node(e_tk tk, unsigned int numLine, unsigned int numCol);
    Node(Node const & src);

    ~Node(void);

    Node & operator=(Node const & rhs);

	static std::string convertEnumTk(e_tk e);

	e_tk getToken(void) const;
	unsigned int getNumLine() const;
	unsigned int getNumCol() const;
	std::string getValue() const;
	std::string getComment() const;

	void setValue(std::string _valueDouble);
	void setComment(std::string comment);

private:
	Node(void);
	e_tk _token;
	std::string _value;
	std::string _comment;
	unsigned int _numLine;
	unsigned int _numCol;
};

std::ostream & operator<<(std::ostream & os, Node & n);

#endif