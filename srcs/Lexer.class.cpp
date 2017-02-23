#include "Lexer.class.hpp"

Lexer::Lexer(void)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _chunk(NB_TK) {
	this->_modeCin = true;
	this->forEachLine(std::cin);
}

Lexer::Lexer(std::string fileName)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _chunk(NB_TK) {
	std::ifstream ifs(fileName);
	if (!ifs.good()) {
		std::cerr << "File not found" << std::endl;
		exit(1);
	}
	this->_modeCin = false;
	this->forEachLine(ifs);
}

Lexer::Lexer(const Lexer &src) {
	*this = src;
}

Lexer::~Lexer(void) {
	for (std::list<Node*>::iterator it = this->_nodeList.begin(); it != this->_nodeList.end(); ++it) {
		delete *it;
	}
	this->_nodeList.clear();
}

Lexer &Lexer::operator=(const Lexer &rhs) {
	if (this != &rhs) {
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
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_ACCEPT) : (STS_REJECT); \
		case 1: return  STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_3(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT); \
		case 3: return STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_4(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT); \
		case 4: return STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_5(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT); \
		case 5: return STS_REJECT; \
		default: abort(); \
	} \
}


#define TOKEN_DEFINE_6(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 5: return c == str[5] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT); \
		case 6: return STS_REJECT; \
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

e_sts Lexer::tkDSemiCol(const char c, const uint8_t index) {
	std::string str = ";;";
	unsigned int s = this->_chunk[index].length();
	if (this->_modeCin == false)
		return STS_REJECT;
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT);
		case 2: return STS_REJECT;
		default: abort();
	}
}

e_sts Lexer::tkInt8(const char c, const uint8_t index) {
	std::string str = "int8(";
	unsigned int s = this->_chunk[index].length();
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 5: return (c == '-' || isdigit(c)) ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		default: {
			if (isdigit(c)) {
				this->_chunk[index] += c;
				return STS_HUNGRY;
			} else if (c == ')') {
				int i = s - 1;
				if (this->_chunk[index].length() > static_cast<size_t>(i) && isdigit(this->_chunk[index][i])) {
					this->_chunk[index] += c;
					return STS_ACCEPT;
				} else {
					return STS_REJECT;
				}
			}
			return STS_REJECT;
		}
	}
}

e_sts Lexer::tkInt16(const char c, const uint8_t index) {
	std::string str = "int16(";
	unsigned int s = this->_chunk[index].length();
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 5: return c == str[5] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		default: {
			if (isdigit(c)) {
				this->_chunk[index] += c;
				return STS_HUNGRY;
			} else if (c == ')') {
				int i = s - 1;
				if (this->_chunk[index].length() > static_cast<size_t>(i) && isdigit(this->_chunk[index][i])) {
					this->_chunk[index] += c;
					return STS_ACCEPT;
				} else {
					return STS_REJECT;
				}
			}
			return STS_REJECT;
		}
	}
}

e_sts Lexer::tkInt32(const char c, const uint8_t index) {
	std::string str = "int32(";
	unsigned int s = this->_chunk[index].length();
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 5: return c == str[5] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		default: {
			if (isdigit(c)) {
				this->_chunk[index] += c;
				return STS_HUNGRY;
			} else if (c == ')') {
				int i = s - 1;
				if (this->_chunk[index].length() > static_cast<size_t>(i) && isdigit(this->_chunk[index][i])) {
					this->_chunk[index] += c;
					return STS_ACCEPT;
				} else {
					return STS_REJECT;
				}
			}
			return STS_REJECT;
		}
	}
}

e_sts Lexer::tkFloat(const char c, const uint8_t index) {
	std::string str = "float(";
	unsigned int s = this->_chunk[index].length();
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 5: return c == str[5] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 6: return (c == '-' || isdigit(c)) ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		default: {
			if (isdigit(c)) {
				this->_chunk[index] += c;
				return STS_HUNGRY;
			} else if (c == '.') {
				int i = s - 1;
				if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
					this->_chunk[index] += c;
					return STS_HUNGRY;
				} else
					return STS_REJECT;
			} else if (c == ')') {
				int i = s - 1;
				int NbPoint = std::count(this->_chunk[index].begin(), this->_chunk[index].end(), '.');
				if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i]) && NbPoint == 1) {
					this->_chunk[index] += c;
					return STS_ACCEPT;
				} else
					return STS_REJECT;
			}
			return STS_REJECT;
		}
	}
}

e_sts Lexer::tkDouble(const char c, const uint8_t index) {
	std::string str = "double(";
	unsigned int s = this->_chunk[index].length();
	switch(s) {
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT);
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 3: return c == str[3] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 4: return c == str[4] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 5: return c == str[5] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 6: return c == str[6] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		case 7: return (c == '-' || isdigit(c)) ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT);
		default: {
			if (isdigit(c)) {
				this->_chunk[index] += c;
				return STS_HUNGRY;
			} else if (c == '.') {
				int i = s - 1;
				if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i])) {
					this->_chunk[index] += c;
					return STS_HUNGRY;
				} else
					return STS_REJECT;
			} else if (c == ')') {
				int i = s - 1;
				int NbPoint = std::count(this->_chunk[index].begin(), this->_chunk[index].end(), '.');
				if (this->_chunk[index].length() > static_cast<size_t >(i) && isdigit(this->_chunk[index][i]) && NbPoint == 1) {
					this->_chunk[index] += c;
					return STS_ACCEPT;
				} else
					return STS_REJECT;
			}
			return STS_REJECT;
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
	if (token != NB_TK && token != TK_DSEMI_COL && token != TK_COMMENT)
		this->_nodeList.push_back(new Node(token, this->_chunk[index], line, col));
	return token;
}

void Lexer::pushError(unsigned int line, unsigned int col) {
	e_tk token = getTokenFound();
	this->_errorList.push_back(new Node(token, "", line, col));
}

void Lexer::forEachLine(std::istream & is) {
	std::string line;
	unsigned int numLine = 0;

	while (getline(is, line)) {
		line += "\n";
		if (this->forEachChar(line, numLine) == true)
			break ;
		if (line.length() > 1)
			this->_nodeList.push_back(new Node(TK_END_LINE, "\n", numLine, line.length()));
		numLine++;
	}
}

bool Lexer::forEachChar(std::string & line, unsigned int numLine) {
	unsigned int tmpCol = 0;
	unsigned int numCol = 0;
	std::string::iterator it = line.begin();

	while (it != line.end()) {
		e_tk token = findCaracter(*it, numCol, numLine, false);
		//std::cout << Node::convertEnumTk(token) << " " << *it << std::endl;
		if (token != NB_TK)
			numCol = tmpCol;
		if (token == TK_DSEMI_COL)
			return true;
		if (token == TK_COMMENT)
			return false;
		it++;
		tmpCol++;
	}
	this->pushToken(numLine, numCol);
	return false;
}

e_tk Lexer::findCaracter(char c, unsigned int numCol, unsigned int numLine, bool reCheck) {
	if (matchToken(c)) {
		this->updateStatus();
	} else {
		e_tk token = this->pushToken(numLine, numCol);
		//std::cout << Node::convertEnumTk(token) << " " << c << std::endl;
		if (token == TK_DSEMI_COL)
			return TK_DSEMI_COL;
		if (token == TK_COMMENT)
			return TK_COMMENT;
		if (token == NB_TK) {
			if (reCheck == false)
				this->findCaracter(c, numCol, numLine, true);
			else
				this->pushError(numLine, numCol);
		} else
			this->findCaracter(c, numCol, numLine, false);

		return token;
	}
	return NB_TK;
}

Lexer::UnknownTokenException::UnknownTokenException(void) { }

Lexer::UnknownTokenException::UnknownTokenException(const Lexer::UnknownTokenException &src) {
	*this = src;
}

Lexer::UnknownTokenException::~UnknownTokenException(void) throw() { }

Lexer::UnknownTokenException & Lexer::UnknownTokenException::operator=(const Lexer::UnknownTokenException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Lexer::UnknownTokenException::what() const throw() {
	return "Unknown Token Exception";
}

void Lexer::printError(void) {
	for (std::list<Node *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		Lexer::UnknownTokenException e;
		e.what();
		std::cerr << e.what() << ", col: " << (*it)->getNumCol() << " line: " << (*it)->getNumLine() << std::endl;
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
		std::cout << Node::convertEnumTk(tk) << "\t";
		std::cout << this->_status[i];
		std::cout << " |" << this->_chunk[i] << "|" << std::endl;
	}
}

std::ostream &operator<<(std::ostream &os, Status &s) {
	os << "prev: " << Lexer::convertStsEnum(s.prev);
	os << " | curr: " << Lexer::convertStsEnum(s.curr);
	return os;
}
