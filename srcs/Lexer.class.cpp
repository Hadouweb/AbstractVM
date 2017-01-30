#include "Lexer.class.hpp"

Lexer::Lexer(void) {
	this->read();
}

Lexer::Lexer(std::string fileName) {
	this->read(fileName);
}

Lexer::Lexer(const Lexer &src) {
	*this = src;
}

Lexer::~Lexer(void) {
	// TODO
}

Lexer &Lexer::operator=(const Lexer &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

void Lexer::read(void) {
	for (std::string line; std::getline(std::cin, line);) {
		std::cout << line << std::endl;
	}
}

void Lexer::read(std::string fileName) {
	std::ifstream ifs(fileName);
	std::string line;
	while (std::getline(ifs, line)) {
		std::cout << line << std::endl;
	}
}
