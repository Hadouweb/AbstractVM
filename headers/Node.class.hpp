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
	Node(e_tk tk, unsigned int numLine);
    Node(Node const & src);

    ~Node(void);

    Node & operator=(Node const & rhs);
	e_tk getToken(void) const;
    unsigned int getNumLine() const;
	static std::string convertEnumTk(e_tk e);

	int8_t getValueInt8() const;
	int16_t getValueInt16() const;
	int32_t getValueInt32() const;
	float getValueFloat() const;
	double getValueDouble() const;

	void setValueDouble(double _valueDouble);
	void setValueFloat(float _valueFloat);
	void setValueInt32(int32_t _valueInt32);
	void setValueInt16(int16_t _valueInt16);
	void setValueInt8(int8_t _valueInt8);

private:
	Node(void);
	e_tk _token;
	int8_t _valueInt8;
	int16_t _valueInt16;
	int32_t _valueInt32;
	float _valueFloat;
	double _valueDouble;
	unsigned int _numLine;
};

std::ostream & operator<<(std::ostream & os, Node & n);

#endif