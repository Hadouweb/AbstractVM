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

void Lexer::tk_instr_push(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("push") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_PUSH, numLine, numCol));
	}
}

void Lexer::tk_instr_pop(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("pop") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_POP, numLine, numCol));
	}
}

void Lexer::tk_instr_dump(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("dump") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_DUMP, numLine, numCol));
	}
}

void Lexer::tk_instr_assert(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("assert") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_ASSERT, numLine, numCol));
	}
}

void Lexer::tk_instr_add(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("add") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_ADD, numLine, numCol));
	}
}

void Lexer::tk_instr_sub(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("sub") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_SUB, numLine, numCol));
	}
}

void Lexer::tk_instr_mul(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("mul") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_MUL, numLine, numCol));
	}
}

void Lexer::tk_instr_div(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("div") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_DIV, numLine, numCol));
	}
}

void Lexer::tk_instr_mod(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("mod") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_MOD, numLine, numCol));
	}
}

void Lexer::tk_instr_print(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("print") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_PRINT, numLine, numCol));
	}
}

void Lexer::tk_instr_exit(std::string str, unsigned int numLine, unsigned int numCol) {
	if (str.compare("exit") == 0) {
		this->_nodeList.push_back(new Node(TK_INSTR_EXIT, numLine, numCol));
	}
}

bool Lexer::tk_comment(std::string str, std::string part, unsigned int numLine, unsigned int numCol) {
	std::size_t index = part.find(';');
	if (index != std::string::npos) {
		std::size_t index = str.find(';');
		std::string comment = str.substr(index, str.length());
		Node *n = new Node(TK_COMMENT, numLine, numCol);
		n->setComment(comment);
		this->_nodeList.push_back(n);
		return true;
	}
	return false;
}

void Lexer::tk_value_int_8(std::string str, unsigned int numLine, unsigned int numCol) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int8") == 0) {
		Node *n = new Node(TK_VALUE_INT_8, numLine, numCol);
		n->setValue(val);
		this->_nodeList.push_back(n);
	}
}

void Lexer::tk_value_int_16(std::string str, unsigned int numLine, unsigned int numCol) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int16") == 0) {
		Node *n = new Node(TK_VALUE_INT_16, numLine, numCol);
		n->setValue(val);
		this->_nodeList.push_back(n);
	}
}

void Lexer::tk_value_int_32(std::string str, unsigned int numLine, unsigned int numCol) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("int32") == 0) {
		Node *n = new Node(TK_VALUE_INT_32, numLine, numCol);
		n->setValue(val);
		this->_nodeList.push_back(n);
	}
}

void Lexer::tk_value_float(std::string str, unsigned int numLine, unsigned int numCol) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("float") == 0) {
		Node *n = new Node(TK_VALUE_FLOAT, numLine, numCol);
		n->setValue(val);
		this->_nodeList.push_back(n);
	}
}

void Lexer::tk_value_double(std::string str, unsigned int numLine, unsigned int numCol) {
	unsigned long index = str.find("(");
	std::string type = str.substr(0, index);
	str.erase(0, index);
	std::string val = str.substr(0, str.length());
	val.erase(std::remove(val.begin(), val.end(), '('), str.end());
	val.erase(std::remove(val.begin(), val.end(), ')'), str.end());
	if (type.compare("double") == 0) {
		Node *n = new Node(TK_VALUE_DOUBLE, numLine, numCol);
		n->setValue(val);
		this->_nodeList.push_back(n);
	}
}

void Lexer::parseLine(std::string line, unsigned int numLine) {
	std::istringstream is(line);
	std::string part;
	unsigned int numCol = 0;
	while (getline(is, part, ' ')) {
		if (!part.empty()) {
			bool tokenComment = tk_comment(is.str(), part, numLine, numCol);
			if (tokenComment == false) {
				for (std::vector<void (Lexer::*)(std::string, unsigned int, unsigned int)>::iterator it = this->_tk.begin(); it != this->_tk.end(); ++it) {
					(this->**it)(part, numLine, numCol);
				}
			}
		}
		numCol += part.length() + 1;
	}
}