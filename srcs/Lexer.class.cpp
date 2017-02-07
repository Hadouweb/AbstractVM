#include "Lexer.class.hpp"

Lexer::Lexer(void) : _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _state(NB_TK) {
	this->read();
}

Lexer::Lexer(std::string fileName) : _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _state(NB_TK) {
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

e_sts Lexer::tkPush(const char c, const uint8_t index) {
	std::string str = "push";

	switch(this->_state[index]) {
		case 0: return c == str[0] ? this->_state[index] = 1, STS_HUNGRY : STS_REJECT;
		case 1: return c == str[1] ? this->_state[index] = 2, STS_HUNGRY : STS_REJECT;
		case 2: return c == str[2] ? this->_state[index] = 3, STS_HUNGRY : STS_REJECT;
		case 3: return c == str[3] ? this->_state[index] = 4, STS_ACCEPT : STS_REJECT;
		case 4: return STS_REJECT;
		default: abort();
	}
}

e_sts Lexer::tkPop(const char c, const uint8_t index) {
	std::string str = "pop";

	switch(this->_state[index]) {
		case 0: return c == str[0] ? this->_state[index] = 1, STS_HUNGRY : STS_REJECT;
		case 1: return c == str[1] ? this->_state[index] = 2, STS_HUNGRY : STS_REJECT;
		case 2: return c == str[2] ? this->_state[index] = 3, STS_ACCEPT : STS_REJECT;
		case 3: return STS_REJECT;
		default: abort();
	}
}

e_sts Lexer::tkDump(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkAssert(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkAdd(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkSub(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkMul(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkDiv(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkMod(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkPrint(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkExit(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkInt8(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkInt16(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkInt32(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkFloat(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkDouble(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

e_sts Lexer::tkComment(const char c, const uint8_t index) {
	if (c && index)
		;
	return STS_REJECT;
}

void Lexer::updateStatus(void) {
	for (int i = 0; i < NB_TK; i++) {
		this->_status[i].prev = this->_status[i].curr;
	}
}

bool Lexer::matchToken(const char c) {
	uint8_t i = 0;
	bool find = false;
	for (tkVectorType::iterator it = this->_tk.begin(); it != this->_tk.end(); ++it) {
		if (this->_status[i].prev != STS_REJECT)
			this->_status[i].curr = (this->**it)(c, i);
		if (this->_status[i].curr != STS_REJECT)
			find = true;
		i++;
	}
	for (int i = 0; i < NB_TK; i++) {
		//std::cout << this->_status[i].curr << std::endl;
	}
	//std::cout << "_______" << std::endl;
	return find;
}

e_tk Lexer::getTokenFound(void) {

	e_tk tk = NB_TK;
	for (int i = 0; i < NB_TK; i++) {
		if (this->_status[i].prev == STS_ACCEPT) {
			tk = static_cast<e_tk>(i);
		}
		this->_status[i].prev = STS_HUNGRY;
		this->_status[i].curr = STS_REJECT;
	}
	return tk;
}

void Lexer::parseLine(std::string line, unsigned int numLine) {
	if (line.length() && numLine)
		;
	unsigned int i = 0;
	unsigned int j = 0;
	std::cout << line << " " << numLine << std::endl;
	while(line[i]) {
		if (this->matchToken(line[i]) == true)
			this->updateStatus();
		else {
			e_tk token = getTokenFound();
			if (token != NB_TK)
				this->_nodeList.push_back(new Node(token, numLine, j));
			j = i;
		}
		i++;
	}
}