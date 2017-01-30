#include <iostream>
#include "Lexer.class.hpp"

int		main(int ac, char **av) {
	if (ac > 1) {
		Lexer l(av[1]);
	} else {
		Lexer l;
	}
}