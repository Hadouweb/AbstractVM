#include "Parser.class.hpp"

Parser::Parser(std::list<Node *> nodeList) {
	try {
		this->makeParsing(nodeList);
	} catch (std::exception & e) {
		if (this->_errorList.size() > 0)
			this->printError();
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

Parser::Parser(Parser const &src) {
	*this = src;
}

Parser::~Parser(void) {
	for (std::list<ParsedNode*>::iterator it = this->_parsedNodeList.begin(); it != this->_parsedNodeList.end(); ++it) {
		delete *it;
	}
	this->_parsedNodeList.clear();
}

Parser &Parser::operator=(Parser const &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

Error::Error(unsigned int col, unsigned int line, std::string type)
	: col(col), line(line), type(type) {

}

void Parser::makeParsing(std::list<Node *> nodeList) {
	bool exit = false;
	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
		if ((*it)->getToken() == TK_INSTR_EXIT)
			exit = true;
		instrMapType::iterator it2 = this->_instrCheckerMap.find((*it)->getToken());
		if (it2 != this->_instrCheckerMap.end()) {
			(this->*it2->second)(it, nodeList);
		}
	}
	if (!exit) {
		throw Parser::ExitExpectedException();
	}
}

std::list<Error*> Parser::getErrorList(void) const {
	return this->_errorList;
}

std::list<ParsedNode *> Parser::getParsedNodeList(void) const {
	return this->_parsedNodeList;
}

Parser::SynthaxException::SynthaxException(void) { }

Parser::SynthaxException::SynthaxException(const Parser::SynthaxException &src) {
	*this = src;
}

Parser::SynthaxException::~SynthaxException(void) throw() { }

Parser::SynthaxException & Parser::SynthaxException::operator=(const Parser::SynthaxException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Parser::SynthaxException::what() const throw() {
	return "Exception: Synthax Error";
}

Parser::ExitExpectedException::ExitExpectedException(void) { }

Parser::ExitExpectedException::ExitExpectedException(const Parser::ExitExpectedException &src) {
	*this = src;
}

Parser::ExitExpectedException::~ExitExpectedException(void) throw() { }

Parser::ExitExpectedException & Parser::ExitExpectedException::operator=(const Parser::ExitExpectedException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Parser::ExitExpectedException::what() const throw() {
	return "Exception: exit instruction is expected at the end";
}

void Parser::printError(void) {
	for (std::list<Error *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		Parser::SynthaxException e;
		std::cerr << e.what() << ", " << (*it)->type << " col : " << (*it)->col << " line : " << (*it)->line << std::endl;
	}
	for (std::list<Error *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		delete *it;
	}
	this->_errorList.clear();
}

void Parser::pushError(unsigned int col, unsigned int line, std::string type) {
	this->_errorList.push_back(new Error(col, line, type));
}

bool Parser::isValue(Node *n) {
	if (n->getToken() == TK_VALUE_DOUBLE ||
		n->getToken() == TK_VALUE_FLOAT ||
		n->getToken() == TK_VALUE_INT_8 ||
		n->getToken() == TK_VALUE_INT_16 ||
		n->getToken() == TK_VALUE_INT_32)
		return true;
	return false;
}

bool Parser::endLine(std::list<Node *>::iterator &it, std::list<Node *> nodeList) {
	while (it != nodeList.end() && (*it)->getToken() == TK_WHITE_SPACE)
		it++;
	if (it != nodeList.end()) {
		if ((*it)->getToken() == TK_COMMENT)
			it++;
		if (it != nodeList.end() && (*it)->getToken() == TK_END_LINE) {
			return true;
		}
	}
	this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "end line expected");
	return false;
}

void Parser::parse_instr_push(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	std::map<e_tk, void (Parser::*)(Node*)>::iterator itType;
	unsigned int col = (*it)->getNumCol();
	unsigned int line = (*it)->getNumLine();
	bool valid = false;

	it++;
	if (it != nodeList.end()) {
		if ((*it)->getToken() == TK_WHITE_SPACE)
			it++;
		else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "space expected");
	} else
		this->pushError(col, line, "space expected");

	col = (*it)->getNumCol();
	line = (*it)->getNumLine();

	if (it != nodeList.end()) {
		if (this->isValue(*it)) {
			valid = true;
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "value type expected");
	} else
		this->pushError(col, line, "value type expected");

	if (valid) {
		this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_PUSH, (*it)->getToken(), (*it)->getValue()));
		it++;
		this->endLine(it, nodeList);
	}
}

void Parser::parse_instr_pop(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_POP, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_dump(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_DUMP, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_assert(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	std::map<e_tk, void (Parser::*)(Node*)>::iterator itType;
	unsigned int col = (*it)->getNumCol();
	unsigned int line = (*it)->getNumLine();
	bool valid = false;

	it++;
	if (it != nodeList.end()) {
		if ((*it)->getToken() == TK_WHITE_SPACE)
			it++;
		else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "space expected");
	} else
		this->pushError(col, line, "space expected");

	col = (*it)->getNumCol();
	line = (*it)->getNumLine();

	if (it != nodeList.end()) {
		if (this->isValue(*it)) {
			valid = true;
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "value type expected");
	} else
		this->pushError(col, line, "value type expected");

	if (valid) {
		this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_ASSERT, (*it)->getToken(), (*it)->getValue()));
		it++;
		this->endLine(it, nodeList);
	}
}

void Parser::parse_instr_add(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_ADD, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_sub(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_SUB, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_mul(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_MUL, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_div(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_DIV, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_mod(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_MOD, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_print(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_PRINT, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_instr_exit(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	this->_parsedNodeList.push_back(new ParsedNode(TK_INSTR_EXIT, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}

void Parser::parse_comment(std::list<Node *>::iterator &it, std::list<Node *> nodeList) {
	//this->_parsedNodeList.push_back(new ParsedNode(TK_COMMENT, NB_TK, ""));
	it++;
	this->endLine(it, nodeList);
}
