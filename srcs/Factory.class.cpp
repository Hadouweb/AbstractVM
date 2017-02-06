#include "Factory.class.hpp"
#include "Operand.class.cpp"

Factory::Factory(void) {
	// TODO
}

Factory::~Factory(void) {
	// TODO
}

const IOperand * Factory::createOperand(eOperandType type, const std::string &value) const {
	int index = static_cast<int>(type);
	return (this->*createFuncArray[index])(value);;
}

const IOperand *Factory::createInt8(const std::string &value) const {
	return new Operand<int8_t>(value);
}

const IOperand *Factory::createInt16(const std::string &value) const {
	return new Operand<int16_t>(value);
}

const IOperand *Factory::createInt32(const std::string &value) const {
	return new Operand<int32_t>(value);
}

const IOperand *Factory::createFloat(const std::string &value) const {
	return new Operand<float>(value);
}

const IOperand *Factory::createDouble(const std::string &value) const {
	return new Operand<double>(value);
}

Factory::Factory(Factory const &src) {
	*this = src;
}

Factory &Factory::operator=(Factory const &rhs) {
	if (this != &rhs) { }
	return *this;
}