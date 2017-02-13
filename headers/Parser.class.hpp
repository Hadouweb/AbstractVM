#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <vector>
#include <iostream>
#include <list>
#include <map>
#include "Node.class.hpp"
#include "ParsedNode.class.hpp"

struct Error {
	Error(unsigned int col, unsigned int line, std::string type);
	unsigned int col;
	unsigned int line;
	std::string type;
};

class Parser {
public:
    Parser(std::list<Node *> nodeList);

    ~Parser(void);

    void makeParsing(std::list<Node *> nodeList);
	std::list<Error*> getErrorList(void) const;
	std::list<ParsedNode*> getParsedNodeList(void) const;
	void printError(void);

private:
	std::list<std::string> _errorStack;
	Parser(Parser const & src);
	Parser & operator=(Parser const & rhs);
	bool isValue(Node *n);
	bool endLine(std::list<Node*>::iterator & it, std::list<Node *> nodeList);
	void pushError(unsigned int col, unsigned int line, std::string type);

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
	void parse_comment(std::list<Node*>::iterator & it, std::list<Node *> nodeList);

	typedef std::map<e_tk, void (Parser::*)(std::list<Node*>::iterator & it, std::list<Node *>) > instrMapType;

	instrMapType _instrCheckerMap = {
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
		{TK_COMMENT, 		&Parser::parse_comment},
    };

	class SynthaxException : public std::exception {
		public:
			SynthaxException(void);
			~SynthaxException(void) throw();
			virtual const char* what() const throw();
		private:
			SynthaxException(SynthaxException const & src);
			SynthaxException & operator=(SynthaxException const & rhs);
	};

	std::list<Error*> _errorList;
	std::list<ParsedNode*> _parsedNodeList;

};

#endif