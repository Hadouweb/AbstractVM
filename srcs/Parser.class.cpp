#include "Parser.class.hpp"

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
		std::map<e_tk, void (*)(std::list<Node*>::iterator & it)>::iterator it2;
		it2 = this->instrCheckerMap.find((*it)->getToken());
		if (it2 != this->instrCheckerMap.end()) {
			((*it2).second)(it);
		} else {
			std::cout << "UNKNOWN : " << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
		}
	}
}

void Parser::parse_instr_push(std::list<Node*>::iterator & it) {


	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_push" << std::endl;
}

void Parser::parse_instr_pop(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_pop" << std::endl;
}

void Parser::parse_instr_dump(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_dump" << std::endl;
}

void Parser::parse_instr_assert(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_assert" << std::endl;
}

void Parser::parse_instr_add(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_add" << std::endl;
}

void Parser::parse_instr_sub(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_sub" << std::endl;
}

void Parser::parse_instr_mul(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_mul" << std::endl;
}

void Parser::parse_instr_div(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_div" << std::endl;
}

void Parser::parse_instr_mod(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_mod" << std::endl;
}

void Parser::parse_instr_print(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_print" << std::endl;
}

void Parser::parse_instr_exit(std::list<Node*>::iterator & it) {
	std::cout << (*it)->convertEnumTk((*it)->getToken()) << std::endl;
	std::cout << "parse_instr_exit" << std::endl;
}
