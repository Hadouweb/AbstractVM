#include "Operand.class.hpp"
#include "VirtualMachine.class.hpp"

template<typename T>
Operand<T>::Operand(void) {

}

template<typename T>
Operand<T>::Operand(std::string pValue, enum eOperandType type)
	: _strValue(pValue), _type(type) {
	this->convertType();
}

template <typename T>
Operand<T>::Operand(Operand const &src)
	: _strValue(src._strValue), _type(src._type), _precision(src._precision) {
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
void Operand<T>::overflowTest(double val) {
	double min = std::numeric_limits<T>::min();
	double max = std::numeric_limits<T>::max();

	//std::cout << "min: " << min << std::endl;
	//std::cout << "max: " << max << std::endl;

	if (val < min || val > max)
		throw Operand::OverflowException();
	else
		this->_value = static_cast<T>(val);
}

template <typename T>
void Operand<T>::convertType(void) {
	//std::cout << "str: " << this->_strValue << std::endl;

	double val = std::atof(this->_strValue.c_str());

	try {
		this->overflowTest(val);
	} catch (std::exception & e) {
		std::cerr << e.what() << " for value: " + this->_strValue;
		exit(1);
	}

	//std::cout << "final val: " << this->_value << std::endl;
	//std::cout << std::endl;
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
	std::stringstream stream;
	double	val;

	stream.str(rhs.toString());
	stream >> val;

	Operand * io = new Operand(*this);
	val = val + this->_value;
	io->_strValue = std::to_string(val);
	io->convertType();
	io->_strValue = std::to_string(io->_value);

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator-(const IOperand &rhs) const {
	std::stringstream stream;
	double	val;

	stream.str(rhs.toString());
	stream >> val;

	Operand * io = new Operand(*this);
	val = val - this->_value;
	io->_strValue = std::to_string(val);
	io->convertType();
	io->_strValue = std::to_string(io->_value);

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator*(const IOperand &rhs) const {
	std::stringstream stream;
	double	val;

	stream.str(rhs.toString());
	stream >> val;

	Operand * io = new Operand(*this);
	val = val * this->_value;
	io->_strValue = std::to_string(val);
	io->convertType();
	io->_strValue = std::to_string(io->_value);

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator/(const IOperand &rhs) const {
	std::stringstream stream;
	double	val;

	stream.str(rhs.toString());
	stream >> val;

	Operand * io = new Operand(*this);
	val = val / this->_value;
	io->_strValue = std::to_string(val);
	io->convertType();
	io->_strValue = std::to_string(io->_value);

	return io;
}

template <typename T>
const IOperand *Operand<T>::operator%(const IOperand &rhs) const {
	std::stringstream stream;
	double	val;

	stream.str(rhs.toString());
	stream >> val;

	Operand * io = new Operand(*this);
	val = std::fmod(val, this->_value);
	io->_strValue = std::to_string(val);
	io->convertType();
	io->_strValue = std::to_string(io->_value);

	return io;
}

template <typename T>
const std::string &Operand<T>::toString(void) const {
	return this->_strValue;
}

template <typename T>
Operand<T>::OverflowException::OverflowException(void) { }

template <typename T>
Operand<T>::OverflowException::~OverflowException(void) throw() { }

template <typename T>
const char *Operand<T>::OverflowException::what() const throw() {
	return "Overflow Exception";
}

template <typename T>
Operand<T>::OverflowException::OverflowException(const Operand::OverflowException &src) {
	*this = src;
}

template <typename T>
typename Operand<T>::OverflowException &Operand<T>::OverflowException::operator=(const Operand<T>::OverflowException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}
