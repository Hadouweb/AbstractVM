#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include <map>
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
	std::map<std::string, void (Lexer::*)(std::string, unsigned int, unsigned int)> _tk = {
		{"push", 	&Lexer::tk_instr_push},
		{"pop", 	&Lexer::tk_instr_pop},
		{"dump", 	&Lexer::tk_instr_dump},
		{"assert", 	&Lexer::tk_instr_assert},
		{"add", 	&Lexer::tk_instr_add},
		{"sub", 	&Lexer::tk_instr_sub},
		{"mul", 	&Lexer::tk_instr_mul},
		{"div", 	&Lexer::tk_instr_div},
		{"mod", 	&Lexer::tk_instr_mod},
		{"print", 	&Lexer::tk_instr_print},
		{"exit", 	&Lexer::tk_instr_exit},
		{"int8", 	&Lexer::tk_value_int_8},
		{"int16", 	&Lexer::tk_value_int_16},
		{"int32", 	&Lexer::tk_value_int_32},
		{"float", 	&Lexer::tk_value_float},
		{"double", 	&Lexer::tk_value_double},
	};
};

#endif