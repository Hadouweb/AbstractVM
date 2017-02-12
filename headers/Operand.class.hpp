#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include <string>
#include <typeinfo>
#include "IOperand.class.hpp"
#include <climits>
#include <list>
#include "Factory.class.hpp"
#include <sstream>
#include <cmath>

template <typename T>
class Operand : public IOperand {
public:
	Operand(std::string pValue, enum eOperandType type);
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

	class OverflowException : public std::exception {
		public:
			OverflowException(void);
			OverflowException(OverflowException const & src);
			~OverflowException(void) throw();
			virtual const char* what() const throw();
		private:
			OverflowException & operator=(OverflowException const & rhs);
	};

private:
	std::string _strValue;
	eOperandType _type;
	int _precision;
	T _value;

	Operand(void);
	void convertType(void);
	void overflowTest(double val);
};

#endif