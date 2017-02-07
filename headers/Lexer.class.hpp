#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include "Node.class.hpp"

class Node;

enum	e_sts
{
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

struct Status {
	e_sts prev;
	e_sts curr;
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
	std::list<Node*> getNodeList(void);

private:
	void parseLine(std::string line, unsigned int numLine);
	void updateStatus(void);
	bool matchToken(const char c);
	e_tk getTokenFound(void);

	e_sts tkPush(const char c, const uint8_t index);
	e_sts tkPop(const char c, const uint8_t index);
	e_sts tkDump(const char c, const uint8_t index);
	e_sts tkAssert(const char c, const uint8_t index);
	e_sts tkAdd(const char c, const uint8_t index);
	e_sts tkSub(const char c, const uint8_t index);
	e_sts tkMul(const char c, const uint8_t index);
	e_sts tkDiv(const char c, const uint8_t index);
	e_sts tkMod(const char c, const uint8_t index);
	e_sts tkPrint(const char c, const uint8_t index);
	e_sts tkExit(const char c, const uint8_t index);
	e_sts tkInt8(const char c, const uint8_t index);
	e_sts tkInt16(const char c, const uint8_t index);
	e_sts tkInt32(const char c, const uint8_t index);
	e_sts tkFloat(const char c, const uint8_t index);
	e_sts tkDouble(const char c, const uint8_t index);
	e_sts tkComment(const char c, const uint8_t index);

	std::list<Node*> _nodeList;

	typedef std::vector<e_sts (Lexer::*)(const char c, const uint8_t index)> tkVectorType;
	tkVectorType _tk = {
		&Lexer::tkPush,
		&Lexer::tkPop,
		&Lexer::tkDump,
		&Lexer::tkAssert,
		&Lexer::tkAdd,
		&Lexer::tkSub,
		&Lexer::tkMul,
		&Lexer::tkDiv,
		&Lexer::tkMod,
		&Lexer::tkPrint,
		&Lexer::tkExit,
		&Lexer::tkInt8,
		&Lexer::tkInt16,
		&Lexer::tkInt32,
		&Lexer::tkFloat,
		&Lexer::tkDouble,
		&Lexer::tkComment,
	};

	std::vector<Status> _status;
	std::vector<uint8_t> _state;
};

#endif