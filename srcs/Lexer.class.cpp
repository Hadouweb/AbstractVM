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
	unsigned int i = 0;
	for (std::string line; std::getline(std::cin, line);) {
		this->parseLine(line, i);
		i++;
	}
}

void Lexer::read(std::string fileName) {
unsigned int i = 0;
	std::ifstream ifs(fileName);
	std::string line;
	while (std::getline(ifs, line)) {
		this->parseLine(line, i);
		i++;
	}
}

std::list<Node*> Lexer::getNodeList(void) {
	return this->_nodeList;
}

Node * Lexer::tk_instr_push(std::string str, unsigned int numLine) {
	if (str.compare("push") == 0) {
		return new Node(TK_INSTR_PUSH, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_pop(std::string str, unsigned int numLine) {
	if (str.compare("pop") == 0) {
		return new Node(TK_INSTR_POP, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_dump(std::string str, unsigned int numLine) {
	if (str.compare("dump") == 0) {
		return new Node(TK_INSTR_DUMP, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_assert(std::string str, unsigned int numLine) {
	if (str.compare("assert") == 0) {
		return new Node(TK_INSTR_ASSERT, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_add(std::string str, unsigned int numLine) {
	if (str.compare("add") == 0) {
		return new Node(TK_INSTR_ADD, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_sub(std::string str, unsigned int numLine) {
	if (str.compare("sub") == 0) {
		return new Node(TK_INSTR_SUB, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_mul(std::string str, unsigned int numLine) {
	if (str.compare("mul") == 0) {
		return new Node(TK_INSTR_MUL, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_div(std::string str, unsigned int numLine) {
	if (str.compare("div") == 0) {
		return new Node(TK_INSTR_DIV, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_mod(std::string str, unsigned int numLine) {
	if (str.compare("mod") == 0) {
		return new Node(TK_INSTR_MOD, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_print(std::string str, unsigned int numLine) {
	if (str.compare("print") == 0) {
		return new Node(TK_INSTR_PRINT, numLine);
	}
	return NULL;
}

Node * Lexer::tk_instr_exit(std::string str, unsigned int numLine) {
	if (str.compare("exit") == 0) {
		return new Node(TK_INSTR_EXIT, numLine);
	}
	return NULL;
}

Node * Lexer::tk_comment(std::string str, unsigned int numLine) {
	if (str.compare(";") == 0) {
		return new Node(TK_COMMENT, numLine);
	}
	return NULL;
}

Node *Lexer::tk_value_int_8(std::string str, unsigned int numLine) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int8") == 0) {
		Node *n = new Node(TK_VALUE_INT_8, numLine);
		n->setValueInt8(std::stoi(val));
		return n;
	}
	return NULL;
}

Node *Lexer::tk_value_int_16(std::string str, unsigned int numLine) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int16") == 0) {
		Node *n = new Node(TK_VALUE_INT_16, numLine);
		n->setValueInt16(std::stoi(val));
		return n;
	}
	return NULL;
}

Node *Lexer::tk_value_int_32(std::string str, unsigned int numLine) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int32") == 0) {
		Node *n = new Node(TK_VALUE_INT_32, numLine);
		n->setValueInt32(std::stoi(val));
		return n;
	}
	return NULL;
}

Node *Lexer::tk_value_float(std::string str, unsigned int numLine) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("float") == 0) {
		Node *n = new Node(TK_VALUE_FLOAT, numLine);
		n->setValueFloat(std::stof(val));
		return n;
	}
	return NULL;
}

Node *Lexer::tk_value_double(std::string str, unsigned int numLine) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("double") == 0) {
		Node *n = new Node(TK_VALUE_DOUBLE, numLine);
		n->setValueDouble(std::stod(val));
		return n;
	}
	return NULL;
}

void Lexer::parseLine(std::string line, unsigned int numLine) {
	std::istringstream is(line);
	std::string part;
	while (getline(is, part, ' ')) {
		if (!part.empty()) {
			for (std::vector<Node * (*)(std::string, unsigned int)>::iterator it = this->_tk.begin(); it != this->_tk.end(); ++it) {
				Node * n = (*it)(part, numLine);
				if (n != NULL)
					this->_nodeList.push_back(n);
			}
			/*std::list<Node*> nodeList = this->getNodeList();
			for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
				std::cout << *(*it);
			}*/
		}
	}
}
