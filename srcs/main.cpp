#include <iostream>
#include "VirtualMachine.class.hpp"
#include "Lexer.class.hpp"
#include "Parser.class.hpp"

int		main(int ac, char **av) {
	Lexer * l;

	if (ac > 1)
		l = new Lexer(av[1]);
	else
		l = new Lexer();

	std::list<Node*> nodeList = l->getNodeList();
	std::list<Node*> errorList = l->getErrorList();

	if (errorList.size() > 0) {
		l->printError();
		exit(1);
	}

	// DEBUG

	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
		//std::cout << *(*it);
	}


	Parser p(nodeList);
	//delete l;

	std::list<Error*> errorListParser = p.getErrorList();
	std::list<ParsedNode*> parsedListParser = p.getParsedNodeList();

	if (errorListParser.size() > 0) {
		p.printError();
		exit(1);
	}

	// DEBUG
	/*
	for (std::list<ParsedNode*>::iterator it = parsedListParser.begin(); it != parsedListParser.end(); ++it) {
		std::cout << *(*it);
	}
	*/

	VirtualMachine VM(parsedListParser);

	return 0;
}