#include <iostream>
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
	} else {
		Lexer l;
	}
}