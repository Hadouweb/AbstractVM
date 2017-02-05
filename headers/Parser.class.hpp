#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <iostream>
#include <list>
#include "Node.class.hpp"
#include <map>

class Parser {
public:
    Parser(std::list<Node *> nodeList);
    Parser(Parser const & src);

    ~Parser(void);

    Parser & operator=(Parser const & rhs);
    void makeParsing(std::list<Node *> nodeList);

	static void parse_instr_push(std::list<Node*>::iterator & it);
	static void parse_instr_pop(std::list<Node*>::iterator & it);
	static void parse_instr_dump(std::list<Node*>::iterator & it);
	static void parse_instr_assert(std::list<Node*>::iterator & it);
	static void parse_instr_add(std::list<Node*>::iterator & it);
	static void parse_instr_sub(std::list<Node*>::iterator & it);
	static void parse_instr_mul(std::list<Node*>::iterator & it);
	static void parse_instr_div(std::list<Node*>::iterator & it);
	static void parse_instr_mod(std::list<Node*>::iterator & it);
	static void parse_instr_print(std::list<Node*>::iterator & it);
	static void parse_instr_exit(std::list<Node*>::iterator & it);

    std::map<e_tk, void (*)(std::list<Node*>::iterator & it)> instrCheckerMap = {
    	{TK_INSTR_PUSH, Parser::parse_instr_push},
		{TK_INSTR_POP, Parser::parse_instr_pop},
		{TK_INSTR_DUMP, Parser::parse_instr_dump},
		{TK_INSTR_ASSERT, Parser::parse_instr_assert},
		{TK_INSTR_ADD, Parser::parse_instr_add},
		{TK_INSTR_SUB, Parser::parse_instr_sub},
		{TK_INSTR_MUL, Parser::parse_instr_mul},
		{TK_INSTR_DIV, Parser::parse_instr_div},
		{TK_INSTR_MOD, Parser::parse_instr_mod},
		{TK_INSTR_PRINT, Parser::parse_instr_print},
		{TK_INSTR_EXIT, Parser::parse_instr_exit},
    };
};

#endif