#include "Parser.class.hpp"
#include "ParsedNode.class.cpp"

Parser::Parser(std::list<Node *> nodeList) {
	this->makeParsing(nodeList);
}

Parser::Parser(Parser const &src) {
	*this = src;
}

Parser::~Parser(void) {
	// TODO
}

Parser &Parser::operator=(Parser const &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

void Parser::makeParsing(std::list<Node *> nodeList) {
	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
		std::map<e_tk, void (*)(std::list<Node*>::iterator & it, std::list<Node *> nodeList)>::iterator it2;
		it2 = this->_instrCheckerMap.find((*it)->getToken());
		if (it2 != this->_instrCheckerMap.end()) {
			((*it2).second)(it, nodeList);
		} else {
			std::cout << "UNKNOWN : " << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
		}
	}
}

void Parser::parse_value_int_8(Node * n) {
	std::cout << n->convertEnumTk(n->getToken()) << std::endl;
	std::cout << "parse_value_int_8" << std::endl;
}

void Parser::parse_value_int_16(Node * n) {
	std::cout << n->convertEnumTk(n->getToken()) << std::endl;
	std::cout << "parse_value_int_16" << std::endl;
}

void Parser::parse_value_int_32(Node * n) {
	std::cout << n->convertEnumTk(n->getToken()) << std::endl;
	std::cout << "parse_value_int_32" << std::endl;
}

void Parser::parse_value_float(Node * n) {
	std::cout << n->convertEnumTk(n->getToken()) << std::endl;
	std::cout << "parse_value_float" << std::endl;
}

void Parser::parse_value_double(Node * n) {
	std::cout << n->convertEnumTk(n->getToken()) << std::endl;
	std::cout << "parse_value_double" << std::endl;
}

void Parser::parse_instr_push(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	std::map<e_tk, void (*)(Node*)>::iterator it2;
	++it;
	if (it != nodeList.end()) {
		it2 = Parser::typeCheckerMap.find((*it)->getToken());
		if (it2 != Parser::typeCheckerMap.end())
			((*it2).second)(*it);
		else
			;// Error;
	}
	else
		;// Error;

	ParsedNode<> pN((*it)->getToken(), true);

	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_push" << std::endl;
}

void Parser::parse_instr_pop(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_pop" << std::endl;
}

void Parser::parse_instr_dump(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_dump" << std::endl;
}

void Parser::parse_instr_assert(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_assert" << std::endl;
}

void Parser::parse_instr_add(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_add" << std::endl;
}

void Parser::parse_instr_sub(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_sub" << std::endl;
}

void Parser::parse_instr_mul(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_mul" << std::endl;
}

void Parser::parse_instr_div(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_div" << std::endl;
}

void Parser::parse_instr_mod(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_mod" << std::endl;
}

void Parser::parse_instr_print(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_print" << std::endl;
}

void Parser::parse_instr_exit(std::list<Node*>::iterator & it, std::list<Node *> nodeList) {
	if (nodeList.size())
		;
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_exit" << std::endl;
}

std::map<e_tk, void (*)(Node *)> Parser::makeTypeCheckerMap(void) {
	std::map<e_tk, void (*)(Node *)> typeCheckerMap = {
			{TK_VALUE_INT_8, Parser::parse_value_int_8},
			{TK_VALUE_INT_16, Parser::parse_value_int_16},
			{TK_VALUE_INT_32, Parser::parse_value_int_32},
			{TK_VALUE_FLOAT, Parser::parse_value_float},
			{TK_VALUE_DOUBLE, Parser::parse_value_double},
	};
	return typeCheckerMap;
}

std::map<e_tk, void (*)(Node *)> Parser::typeCheckerMap = Parser::makeTypeCheckerMap();
