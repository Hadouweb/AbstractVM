#include "Operand.class.hpp"
#include "VirtualMachine.class.hpp"

template<typename T>
Operand<T>::Operand(void) { }

template<typename T>
Operand<T>::Operand(std::string pValue, enum eOperandType type)
	: _strValue(pValue), _type(type) {
	this->convertType();
}

template <typename T>
Operand<T>::Operand(Operand const &src)
	: _strValue(src._strValue), _type(src._type) {
	*this = src;
}

template <typename T>
Operand<T>::~Operand(void) { }

template <typename T>
Operand<T> &Operand<T>::operator=(Operand const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

template <typename T>
void Operand<T>::overflowTest(double val) {
	double min = std::numeric_limits<T>::min();
	double max = std::numeric_limits<T>::max();

	if (val > max)
		throw std::overflow_error("Overflow exception");
	else if (val < min)
		throw std::underflow_error("Underflow exception");
	else
		this->_value = static_cast<T>(val);
}

template <typename T>
void Operand<T>::convertType(void) {
	double val = std::atof(this->_strValue.c_str());

	try {
		this->overflowTest(val);
	} catch (std::exception & e) {
		std::cerr << e.what() << " for value: " + this->_strValue;
		exit(1);
	}
}

template <typename T>
int Operand<T>::getPrecision(void) const {
	return static_cast<int>(this->getType());
}

template <typename T>
eOperandType Operand<T>::getType(void) const {
	return this->_type;
}

template <typename T>
const IOperand *Operand<T>::operator+(const IOperand &rhs) const {
	eOperandType mostAccurate;
	std::stringstream stream;
	double val;

	if (this->getPrecision() > rhs.getPrecision())
		mostAccurate = this->getType();
	else
		mostAccurate = rhs.getType();

	stream.str(rhs.toString());
	stream >> val;

	val = val + this->_value;

	stream.str("");
	stream.clear();
	stream << val;

	Factory * f = Factory::getInstance();
	const IOperand * io = f->createOperand(mostAccurate, stream.str());

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator-(const IOperand &rhs) const {
	eOperandType mostAccurate;
	std::stringstream stream;
	double val;

	if (this->getPrecision() > rhs.getPrecision())
		mostAccurate = this->getType();
	else
		mostAccurate = rhs.getType();

	stream.str(rhs.toString());
	stream >> val;

	val = val - this->_value;

	stream.str("");
	stream.clear();
	stream << val;

	Factory * f = Factory::getInstance();
	const IOperand * io = f->createOperand(mostAccurate, stream.str());

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator*(const IOperand &rhs) const {
	eOperandType mostAccurate;
	std::stringstream stream;
	double val;

	if (this->getPrecision() > rhs.getPrecision())
		mostAccurate = this->getType();
	else
		mostAccurate = rhs.getType();

	stream.str(rhs.toString());
	stream >> val;

	val = val * this->_value;

	stream.str("");
	stream.clear();
	stream << val;

	Factory * f = Factory::getInstance();
	const IOperand * io = f->createOperand(mostAccurate, stream.str());

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator/(const IOperand &rhs) const {
	eOperandType mostAccurate;
	std::stringstream stream;
	double val;

	if (this->getPrecision() > rhs.getPrecision())
		mostAccurate = this->getType();
	else
		mostAccurate = rhs.getType();

	stream.str(rhs.toString());
	stream >> val;

	if (this->_value == 0) {
		throw std::logic_error("Exception division by 0");
	}

	val = val / this->_value;

	stream.str("");
	stream.clear();
	stream << val;

	Factory * f = Factory::getInstance();
	const IOperand * io = f->createOperand(mostAccurate, stream.str());

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator%(const IOperand &rhs) const {

	eOperandType mostAccurate;
	std::stringstream stream;
	double val;

	if (this->getPrecision() > rhs.getPrecision())
		mostAccurate = this->getType();
	else
		mostAccurate = rhs.getType();

	stream.str(rhs.toString());
	stream >> val;

	if (this->_value == 0) {
		throw std::logic_error("Exception division by 0");
	}

	val = std::fmod(val, this->_value);

	stream.str("");
	stream.clear();
	stream << val;

	Factory * f = Factory::getInstance();
	const IOperand * io = f->createOperand(mostAccurate, stream.str());

	return io;
}

template <typename T>
const std::string &Operand<T>::toString(void) const {
	return this->_strValue;
}
