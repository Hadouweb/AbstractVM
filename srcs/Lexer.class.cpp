#include "Lexer.class.hpp"

Lexer::Lexer(void)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _state(NB_TK), _chunk(NB_TK) {
	// TODO ERROR IFS
	this->forEachChar(std::cin);
}

Lexer::Lexer(std::string fileName)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _state(NB_TK), _chunk(NB_TK) {
	// TODO ERROR IFS
	std::ifstream ifs(fileName);
	this->forEachChar(ifs);
}

Lexer::Lexer(const Lexer &src) {
	*this = src;
}

Lexer::~Lexer(void) {
	// TODO
	for (std::list<Node*>::iterator it = this->_nodeList.begin(); it != this->_nodeList.end(); ++it) {
		delete *it;
	}
	this->_nodeList.clear();
}

Lexer &Lexer::operator=(const Lexer &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

std::list<Node*> Lexer::getNodeList(void) const {
	return this->_nodeList;
}


std::list<Node *> Lexer::getErrorList(void) const {
	return this->_errorList;
}

#define TOKEN_DEFINE_1(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	switch(this->_state[index]) { \
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_ACCEPT) : (this->_state[index] = 0, STS_REJECT); \
		case 1: return this->_state[index] = 0, STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_3(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	switch(this->_state[index]) { \
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_ACCEPT) : (this->_state[index] = 0, STS_REJECT); \
		case 3: return this->_state[index] = 0, STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_4(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	switch(this->_state[index]) { \
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_ACCEPT) : (this->_state[index] = 0, STS_REJECT); \
		case 4: return this->_state[index] = 0, STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_5(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	switch(this->_state[index]) { \
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_ACCEPT) : (this->_state[index] = 0, STS_REJECT); \
		case 5: return this->_state[index] = 0, STS_REJECT; \
		default: abort(); \
	} \
}


#define TOKEN_DEFINE_6(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	switch(this->_state[index]) { \
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT); \
		case 5: return c == str[5] ? (this->_state[index] = 6, STS_ACCEPT) : (this->_state[index] = 0, STS_REJECT); \
		case 6: return this->_state[index] = 0, STS_REJECT; \
		default: abort(); \
	} \
}

TOKEN_DEFINE_4(tkPush, "push");
TOKEN_DEFINE_3(tkPop, "pop");
TOKEN_DEFINE_4(tkDump, "dump)");
TOKEN_DEFINE_6(tkAssert, "assert");
TOKEN_DEFINE_3(tkAdd, "add");
TOKEN_DEFINE_3(tkSub, "sub");
TOKEN_DEFINE_3(tkMul, "mul");
TOKEN_DEFINE_3(tkDiv, "div");
TOKEN_DEFINE_3(tkMod, "mod");
TOKEN_DEFINE_5(tkPrint, "print");
TOKEN_DEFINE_4(tkExit, "exit");
TOKEN_DEFINE_1(tkComment, ";");
TOKEN_DEFINE_1(tkEndLine, "\n");
TOKEN_DEFINE_1(tkWhiteSpace, " ");

e_sts Lexer::tkInt8(const char c, const uint8_t index) {
	std::string str = "int8(";
	switch(this->_state[index]) {
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 5: return (c == '-' || isdigit(c)) ? (this->_state[index] = 6, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		default: {
			if (this->_state[index] < 0)
				abort();
			else {
				if (isdigit(c)) {
					this->_state[index]++;
					return STS_HUNGRY;
				} else if (c == ')') {
					int i = this->_state[index] - 1;
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
						this->_state[index]++;
						return STS_ACCEPT;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				}
				//std::cout << "[" << c << "]" << std::endl;
				this->_state[index] = 0;
				return STS_REJECT;
			}
		}
	}
}

e_sts Lexer::tkInt16(const char c, const uint8_t index) {
	std::string str = "int16(";
	switch(this->_state[index]) {
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 5: return c == str[5] ? (this->_state[index] = 6, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_state[index] = 7, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		default: {
			if (this->_state[index] < 0)
				abort();
			else {
				if (isdigit(c)) {
					this->_state[index]++;
					return STS_HUNGRY;
				} else if (c == ')') {
					int i = this->_state[index] - 1;
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
						this->_state[index]++;
						return STS_ACCEPT;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				}
				//std::cout << "[" << c << "]" << std::endl;
				this->_state[index] = 0;
				return STS_REJECT;
			}
		}
	}
}

e_sts Lexer::tkInt32(const char c, const uint8_t index) {
	std::string str = "int32(";
	switch(this->_state[index]) {
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 5: return c == str[5] ? (this->_state[index] = 6, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_state[index] = 7, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		default: {
			if (this->_state[index] < 0)
				abort();
			else {
				if (isdigit(c)) {
					this->_state[index]++;
					return STS_HUNGRY;
				} else if (c == ')') {
					int i = this->_state[index] - 1;
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
						this->_state[index]++;
						return STS_ACCEPT;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				}
				//std::cout << "[" << c << "]" << std::endl;
				this->_state[index] = 0;
				return STS_REJECT;
			}
		}
	}
}

e_sts Lexer::tkFloat(const char c, const uint8_t index) {
	std::string str = "float(";
	switch(this->_state[index]) {
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 5: return c == str[5] ? (this->_state[index] = 6, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_state[index] = 7, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		default: {
			if (this->_state[index] < 0)
				abort();
			else {
				if (isdigit(c)) {
					this->_state[index]++;
					return STS_HUNGRY;
				} else if (c == '.') {
					int i = this->_state[index] - 1;
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
						this->_state[index]++;
						return STS_HUNGRY;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				} else if (c == ')') {
					int i = this->_state[index] - 1;
					int NbPoint = std::count(this->_chunk[index].begin(), this->_chunk[index].end(), '.');
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i]) && NbPoint == 1) {
						this->_state[index]++;
						return STS_ACCEPT;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				}
				//std::cout << "[" << c << "]" << std::endl;
				this->_state[index] = 0;
				return STS_REJECT;
			}
		}
	}
}

e_sts Lexer::tkDouble(const char c, const uint8_t index) {
	std::string str = "double(";
	switch(this->_state[index]) {
		case 0: return c == str[0] ? (this->_state[index] = 1, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 1: return c == str[1] ? (this->_state[index] = 2, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 2: return c == str[2] ? (this->_state[index] = 3, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 3: return c == str[3] ? (this->_state[index] = 4, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 4: return c == str[4] ? (this->_state[index] = 5, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 5: return c == str[5] ? (this->_state[index] = 6, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 6: return c == str[6] ? (this->_state[index] = 7, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		case 7: return (c == '-' || isdigit(c)) ? (this->_state[index] = 8, STS_HUNGRY) : (this->_state[index] = 0, STS_REJECT);
		default: {
			if (this->_state[index] < 0)
				abort();
			else {
				if (isdigit(c)) {
					this->_state[index]++;
					return STS_HUNGRY;
				} else if (c == '.') {
					int i = this->_state[index] - 1;
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
						this->_state[index]++;
						return STS_HUNGRY;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				} else if (c == ')') {
					int i = this->_state[index] - 1;
					int NbPoint = std::count(this->_chunk[index].begin(), this->_chunk[index].end(), '.');
					if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i]) && NbPoint == 1) {
						this->_state[index]++;
						return STS_ACCEPT;
					} else {
						this->_state[index] = 0;
						return STS_REJECT;
					}
				}
				//std::cout << "[" << c << "]" << std::endl;
				this->_state[index] = 0;
				return STS_REJECT;
			}
		}
	}
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
		if (this->_status[i].curr != STS_REJECT) {
			find = true;
			this->_chunk[i] += c;
		}
		i++;
	}
	//std::cout << "[" << c << "]" << std::endl;
	//this->printStatus();
	return find;
}

e_tk Lexer::getTokenFound(void) {
	e_tk tk = NB_TK;
	for (int i = 0; i < NB_TK; i++) {
		if (this->_status[i].prev == STS_ACCEPT) {
			tk = static_cast<e_tk>(i);
		} else
			this->_chunk[i].clear();
		this->_status[i].prev = STS_HUNGRY;
		this->_status[i].curr = STS_REJECT;
	}
	return tk;
}

enum e_tk Lexer::pushToken(unsigned int line, unsigned int col) {
	e_tk token = getTokenFound();
	int index = static_cast<int>(token);
	//std::cout << "|" << this->_chunk[index] << "|" << std::endl;
	if (token != NB_TK)
		this->_nodeList.push_back(new Node(token, this->_chunk[index], line, col));
	return token;
}

void Lexer::pushError(unsigned int line, unsigned int col) {
	e_tk token = getTokenFound();
	//std::cout << "|" << this->_chunk[index] << "|" << std::endl;
	this->_errorList.push_back(new Node(token, "", line, col));
}

void Lexer::forEachChar(std::istream & is) {
	unsigned int i = 0;
	unsigned int col = 0;
	unsigned int line = 0;
	char c = is.get();

	while(c >= 0) {
		//std::cout << "|" << c << "|" << std::endl;
		if (matchToken(c)) {
			this->updateStatus();
			c = is.get();
			i++;
		} else {
			e_tk token = this->pushToken(line, col);
			if (token == NB_TK) {
				this->pushError(line, col);
				if (matchToken(c))
					this->updateStatus();
				else {
					c = is.get();
					i++;
				}
			}
			if (token == TK_COMMENT) {
				while((c = is.get()) >= 0 && c != '\n') {
					i++;
				}
			}
			if (token == TK_END_LINE) {
				line++;
				i = 0;
			}
			col = i;
		}
	}
	this->pushToken(line, col);
}

void Lexer::printError(void) {
	for (std::list<Node *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		std::cerr << "Unknown token col: " << (*it)->getNumCol() << " line: " << (*it)->getNumLine() << std::endl;
		delete *it;
	}
	this->_errorList.clear();
}


std::string Lexer::convertStsEnum(enum e_sts sts) {
	switch(sts) {
		case STS_ACCEPT:
			return "STS_ACCEPT";
		case STS_REJECT:
			return "STS_REJECT";
		case STS_HUNGRY:
			return "STS_HUNGRY";
	}
}

void Lexer::printStatus(void) {
	for(int i = 0; i < NB_TK; i++) {
		e_tk tk = static_cast<e_tk>(i);
		std::cout << Node::convertEnumTk(tk) << "\t | ";
		std::cout << (int)this->_state[i] << " | ";
		std::cout << this->_status[i];
	}
}

std::ostream &operator<<(std::ostream &os, Status &s) {
	os << "prev: " << Lexer::convertStsEnum(s.prev);
	os << " | curr: " << Lexer::convertStsEnum(s.curr) << std::endl;
	return os;
}
