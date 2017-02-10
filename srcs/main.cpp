#include <iostream>
#include <VirtualMachine.class.hpp>
#include "Lexer.class.hpp"
#include "Parser.class.hpp"

int		main(int ac, char **av) {
	if (ac > 1) {
		Lexer l(av[1]);

		std::list<Node*> nodeList = l.getNodeList();
		std::list<Node*> errorList = l.getErrorList();

		if (errorList.size() > 0) {
			l.printError();
			exit(1);
		}

		for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
			//std::cout << *(*it);
		}

		Parser p(nodeList);

		std::list<Error*> errorListParser = p.getErrorList();
		std::list<ParsedNode*> parsedListParser = p.getParsedNodeList();

		if (errorListParser.size() > 0) {
			p.printError();
			exit(1);
		}

		for (std::list<ParsedNode*>::iterator it = parsedListParser.begin(); it != parsedListParser.end(); ++it) {
			//std::cout << *(*it);
		}

		VirtualMachine VM(parsedListParser);

		std::list<std::string> eList = VirtualMachine::exceptionList;

		for (std::list<std::string>::iterator it = eList.begin(); it != eList.end(); ++it) {
			std::cout << (*it) << std::endl;
		}

		VM.printOpStack();


	} else {
		Lexer l;
	}
}