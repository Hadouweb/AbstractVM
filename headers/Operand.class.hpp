#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include <string>
#include "IOperand.class.hpp"

template <typename T>
class Operand : public IOperand {
public:
    Operand(void);
    Operand(Operand const & src);

    ~Operand(void);

    Operand & operator=(Operand const & rhs);

	virtual int getPrecision(void) const override;
	virtual eOperandType getType(void) const override;
	virtual const IOperand *operator+(IOperand const &rhs) const override;
	virtual const IOperand *operator-(IOperand const &rhs) const override;
	virtual const IOperand *operator*(IOperand const &rhs) const override;
	virtual const IOperand *operator/(IOperand const &rhs) const override;
	virtual const IOperand *operator%(IOperand const &rhs) const override;
	virtual const std::string &toString(void) const override;

private:
	T _value;
	const int _precision;
	const eOperandType _type;

};

#endif