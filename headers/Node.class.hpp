#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

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
	TK_VALUE_INT_8,
	TK_VALUE_INT_16,
	TK_VALUE_INT_32,
	TK_VALUE_FLOAT,
	TK_VALUE_DOUBLE,
	TK_COMMENT,
	TK_END_LINE,
	TK_WHITE_SPACE,
	TK_DSEMI_COL,
	NB_TK,
};


class Node {
public:
	Node(e_tk tk, std::string val, unsigned int numLine, unsigned int numCol);
    ~Node(void);

	static std::string convertEnumTk(e_tk e);

	e_tk getToken(void) const;
	unsigned int getNumLine() const;
	unsigned int getNumCol() const;
	std::string getValue() const;

private:
	Node(void);
	Node & operator=(Node const & rhs);
	Node(Node const & src);
	e_tk _token;
	std::string _value;
	unsigned int _numLine;
	unsigned int _numCol;
};

std::ostream & operator<<(std::ostream & os, Node & n);

#endif