#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <iostream>
#include <list>
#include "Node.class.hpp"
#include <map>
#include "ParsedNode.class.hpp"

class Parser {
public:
    Parser(std::list<Node *> nodeList);
    Parser(Parser const & src);

    ~Parser(void);

    Parser & operator=(Parser const & rhs);
    void makeParsing(std::list<Node *> nodeList);

private:
	std::list<std::string> _errorStack;

	void parse_instr_push(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_pop(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_dump(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_assert(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_add(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_sub(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_mul(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_div(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_mod(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_print(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void parse_instr_exit(std::list<Node*>::iterator & it, std::list<Node *> nodeList);

    std::map<e_tk, void (Parser::*)(std::list<Node*>::iterator & it, std::list<Node *> nodeList)> _instrCheckerMap = {
    	{TK_INSTR_PUSH, 	&Parser::parse_instr_push},
		{TK_INSTR_POP, 		&Parser::parse_instr_pop},
		{TK_INSTR_DUMP, 	&Parser::parse_instr_dump},
		{TK_INSTR_ASSERT, 	&Parser::parse_instr_assert},
		{TK_INSTR_ADD, 		&Parser::parse_instr_add},
		{TK_INSTR_SUB, 		&Parser::parse_instr_sub},
		{TK_INSTR_MUL, 		&Parser::parse_instr_mul},
		{TK_INSTR_DIV, 		&Parser::parse_instr_div},
		{TK_INSTR_MOD, 		&Parser::parse_instr_mod},
		{TK_INSTR_PRINT, 	&Parser::parse_instr_print},
		{TK_INSTR_EXIT, 	&Parser::parse_instr_exit},
    };

	void parse_value_int_8(Node * n);
	void parse_value_int_16(Node * n);
	void parse_value_int_32(Node * n);
	void parse_value_float(Node * n);
	void parse_value_double(Node * n);

	std::map<e_tk, void (Parser::*)(Node *)> _typeCheckerMap = {
			{TK_VALUE_INT_8, 	&Parser::parse_value_int_8},
			{TK_VALUE_INT_16, 	&Parser::parse_value_int_16},
			{TK_VALUE_INT_32, 	&Parser::parse_value_int_32},
			{TK_VALUE_FLOAT, 	&Parser::parse_value_float},
			{TK_VALUE_DOUBLE, 	&Parser::parse_value_double},
	};
};

#endif