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

    void makeParsing(void);
	std::list<Error*> getErrorList(void) const;
	std::list<ParsedNode*> getParsedNodeList(void) const;
	void printError(void);

private:
	Parser(Parser const & src);
	Parser & operator=(Parser const & rhs);
	bool isValue(Node *n);
	bool endLine(void);
	void pushError(unsigned int col, unsigned int line, std::string type);

	void parseInstrPush(void);
	void parseInstrPop(void);
	void parseInstrDump(void);
	void parseInstrAssert(void);
	void parseInstrAdd(void);
	void parseInstrSub(void);
	void parseInstrMul(void);
	void parseInstrDiv(void);
	void parseInstrMod(void);
	void parseInstrPrint(void);
	void parseInstrExit(void);

	typedef std::map<e_tk, void (Parser::*)(void) > instrMapType;

	instrMapType _instrCheckerMap = {
    	{TK_INSTR_PUSH, 	&Parser::parseInstrPush},
		{TK_INSTR_POP, 		&Parser::parseInstrPop},
		{TK_INSTR_DUMP, 	&Parser::parseInstrDump},
		{TK_INSTR_ASSERT, 	&Parser::parseInstrAssert},
		{TK_INSTR_ADD, 		&Parser::parseInstrAdd},
		{TK_INSTR_SUB, 		&Parser::parseInstrSub},
		{TK_INSTR_MUL, 		&Parser::parseInstrMul},
		{TK_INSTR_DIV, 		&Parser::parseInstrDiv},
		{TK_INSTR_MOD, 		&Parser::parseInstrMod},
		{TK_INSTR_PRINT, 	&Parser::parseInstrPrint},
		{TK_INSTR_EXIT, 	&Parser::parseInstrExit},
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

	std::list<Node *> _nodeList;
	std::list<Node *>::iterator _currentIt;
	std::list<std::string> _errorStack;
	std::list<Error*> _errorList;
	std::list<ParsedNode*> _parsedNodeList;

};

#endif