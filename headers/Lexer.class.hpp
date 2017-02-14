#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include "Node.class.hpp"

class Node;

enum	e_sts {
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

    ~Lexer(void);
	std::list<Node*> getNodeList(void) const;
	std::list<Node*> getErrorList(void) const;
	void printError(void);

	static std::string convertStsEnum(enum e_sts sts);

private:
	Lexer(Lexer const & src);
	Lexer & operator=(Lexer const & rhs);
	void forEachLine(std::istream & is);
	bool forEachChar(std::string & line, unsigned int numLine);
	void updateStatus(void);
	enum e_tk pushToken(unsigned int line, unsigned int col);
	void pushError(unsigned int line, unsigned int col);
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
	e_sts tkEndLine(const char c, const uint8_t index);
	e_sts tkWhiteSpace(const char c, const uint8_t index);
	e_sts tkDSemiCol(const char c, const uint8_t index);

	std::list<Node*> _nodeList;
	std::list<Node*> _errorList;

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
		&Lexer::tkEndLine,
		&Lexer::tkWhiteSpace,
		&Lexer::tkDSemiCol,
	};

	class UnknownTokenException : public std::exception {
		public:
			UnknownTokenException(void);
			~UnknownTokenException(void) throw();
			virtual const char* what() const throw();
		private:
			UnknownTokenException(UnknownTokenException const & src);
			UnknownTokenException & operator=(UnknownTokenException const & rhs);
	};

	void printStatus(void);

	std::vector<Status> _status;
	std::vector<uint8_t> _state;
	std::vector<std::string> _chunk;
	bool _modeCin;
};

std::ostream & operator<<(std::ostream & os, Status & s);

#endif