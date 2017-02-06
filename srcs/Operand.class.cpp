#include "Operand.class.hpp"

template<typename T>
Operand<T>::Operand(std::string pValue)
	: _precision(8), _type(INT_8), _strValue(pValue) {

}

template <typename T>
Operand<T>::Operand(void) : _precision(8), _type(INT_8) {
	// TODO
}

template <typename T>
Operand<T>::Operand(Operand const &src)
	: _precision(src._precision), _type(src._type), _strValue(src._strValue) {
	*this = src;
}

template <typename T>
Operand<T>::~Operand(void) {
	// TODO
}

template <typename T>
Operand<T> &Operand<T>::operator=(Operand const &rhs) {
	if (this != &rhs) {
		// TODO
	}
	return *this;
}

template <typename T>
int Operand<T>::getPrecision(void) const {
	return this->_precision;
}

template <typename T>
eOperandType Operand<T>::getType(void) const {
	return this->_type;
}

template <typename T>
const IOperand *Operand<T>::operator+(const IOperand &rhs) const {
	return rhs.operator+(*this);
}

template <typename T>
const IOperand *Operand<T>::operator-(const IOperand &rhs) const {
	return rhs.operator-(*this);
}

template <typename T>
const IOperand *Operand<T>::operator*(const IOperand &rhs) const {
	return rhs.operator*(*this);
}

template <typename T>
const IOperand *Operand<T>::operator/(const IOperand &rhs) const {
	return rhs.operator/(*this);
}

template <typename T>
const IOperand *Operand<T>::operator%(const IOperand &rhs) const {
	return rhs.operator%(*this);
}

template <typename T>
const std::string &Operand<T>::toString(void) const {
	return this->_strValue;
}
