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
	static Node * tk_instr_push(std::string str, unsigned int numLine);
	static Node * tk_instr_pop(std::string str, unsigned int numLine);
	static Node * tk_instr_dump(std::string str, unsigned int numLine);
	static Node * tk_instr_assert(std::string str, unsigned int numLine);
	static Node * tk_instr_add(std::string str, unsigned int numLine);
	static Node * tk_instr_sub(std::string str, unsigned int numLine);
	static Node * tk_instr_mul(std::string str, unsigned int numLine);
	static Node * tk_instr_div(std::string str, unsigned int numLine);
	static Node * tk_instr_mod(std::string str, unsigned int numLine);
	static Node * tk_instr_print(std::string str, unsigned int numLine);
	static Node * tk_instr_exit(std::string str, unsigned int numLine);
	static Node * tk_comment(std::string str, unsigned int numLine);
	std::list<Node*> _nodeList;
	std::vector<Node * (*)(std::string, unsigned int)> _instr = {
		Lexer::tk_instr_push,
		Lexer::tk_instr_pop,
		Lexer::tk_instr_dump,
		Lexer::tk_instr_assert,
		Lexer::tk_instr_add,
		Lexer::tk_instr_sub,
		Lexer::tk_instr_mul,
		Lexer::tk_instr_div,
		Lexer::tk_instr_mod,
		Lexer::tk_instr_print,
		Lexer::tk_instr_exit,
		Lexer::tk_comment,
	};
};

#endif