#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>

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
};

enum e_tk_value {
	TK_VALUE_INT_8,
	TK_VALUE_INT_16,
	TK_VALUE_INT_32,
	TK_VALUE_FLOAT,
	TK_VALUE_DOUBLE,
};

class Lexer {
public:
    Lexer(void);
    Lexer(std::string fileName);
    Lexer(Lexer const & src);

    ~Lexer(void);

    Lexer & operator=(Lexer const & rhs);
	void read(void);
	void read(std::string fileName);

private:
	std::vector<std::string> _instr = {
		"push",
		"pop",
		"dump",
		"assert",
		"add",
		"sub",
		"mul",
		"div",
		"mod",
		"print",
		"exit",
	};
};

#endif