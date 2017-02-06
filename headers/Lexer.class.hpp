#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include "Node.class.hpp"

class Node;

class Lexer {
public:
    Lexer(void);
    Lexer(std::string fileName);
    Lexer(Lexer const & src);

    ~Lexer(void);

    Lexer & operator=(Lexer const & rhs);
	void read(void);
	void read(std::string fileName);
	std::list<Node*> getNodeList(void);

private:
	void parseLine(std::string line, unsigned int numLine);

	void tk_instr_push(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_pop(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_dump(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_assert(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_add(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_sub(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_mul(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_div(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_mod(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_print(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_instr_exit(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_value_int_8(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_value_int_16(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_value_int_32(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_value_float(std::string str, unsigned int numLine, unsigned int numCol);
	void tk_value_double(std::string str, unsigned int numLine, unsigned int numCol);
	bool tk_comment(std::string str, std::string part, unsigned int numLine, unsigned int numCol);

	std::list<Node*> _nodeList;
	std::vector<void (Lexer::*)(std::string, unsigned int, unsigned int)> _tk = {
		&Lexer::tk_instr_push,
		&Lexer::tk_instr_pop,
		&Lexer::tk_instr_dump,
		&Lexer::tk_instr_assert,
		&Lexer::tk_instr_add,
		&Lexer::tk_instr_sub,
		&Lexer::tk_instr_mul,
		&Lexer::tk_instr_div,
		&Lexer::tk_instr_mod,
		&Lexer::tk_instr_print,
		&Lexer::tk_instr_exit,
		&Lexer::tk_value_int_8,
		&Lexer::tk_value_int_16,
		&Lexer::tk_value_int_32,
		&Lexer::tk_value_float,
		&Lexer::tk_value_double,
	};
};

#endif