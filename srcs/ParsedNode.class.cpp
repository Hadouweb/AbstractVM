#include <ParsedNode.class.hpp>

template <class T>
ParsedNode<T>::ParsedNode(e_tk pTkInstr, bool pHaveValue)
	: _tkInstr(pTkInstr), haveValue(pHaveValue) {

}

template <class T>
ParsedNode<T>::ParsedNode(void)
	: _tkInstr(TK_UNKNOWN), haveValue(false) {
	// TODO
}

template <class T>
ParsedNode<T>::ParsedNode(const ParsedNode &src)
	: _tkInstr(src._tkInstr), haveValue(src.haveValue) {
	*this = src;
}

template <class T>
ParsedNode<T>::~ParsedNode(void) {
	// TODO
}

template <class T>
ParsedNode<T> &ParsedNode<T>::operator=(const ParsedNode &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

template <class T>
void ParsedNode<T>::setValue(IOperand * val) {
	this->_value = val;
}

template <class T>
e_tk ParsedNode<T>::getTkInstr(void) const {
	return this->_tkInstr;
}

template <class T>
bool ParsedNode<T>::getHaveValue(void) const {
	return this->haveValue;
}

template <class T>
IOperand * ParsedNode<T>::getValue(void) const {
	return this->_value;
}

template <class T>
std::ostream &operator<<(std::ostream &os, ParsedNode<T> &pN) {
	os << pN.getTkInstr() << std::endl;
	os << "\t" << pN.getHaveValue() << std::endl;
	if (pN.getHaveValue() == true) {
		os << "\t" << pN.getType() << std::endl;
		os << "\t" << pN.getValue() << std::endl;
	}
	return os;
}
