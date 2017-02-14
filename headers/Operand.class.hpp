#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include <string>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <climits>
#include <list>
#include "IOperand.class.hpp"
#include "Factory.class.hpp"

template <typename T>
class Operand : public IOperand {
public:
	Operand(std::string pValue, enum eOperandType type);
    ~Operand(void);

	virtual int getPrecision(void) const override;
	virtual eOperandType getType(void) const override;
	virtual const IOperand *operator+(IOperand const &rhs) const override;
	virtual const IOperand *operator-(IOperand const &rhs) const override;
	virtual const IOperand *operator*(IOperand const &rhs) const override;
	virtual const IOperand *operator/(IOperand const &rhs) const override;
	virtual const IOperand *operator%(IOperand const &rhs) const override;
	virtual const std::string &toString(void) const override;

private:
	const std::string _strValue;
	const eOperandType _type;
	T _value;

	Operand(void);
	Operand(Operand const & src);
	Operand & operator=(Operand const & rhs);
	void convertType(void);
	void overflowTest(double val);
	bool needInt(eOperandType aType, eOperandType bType) const;
};

#endif