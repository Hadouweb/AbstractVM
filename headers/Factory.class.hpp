#ifndef FACTORY_CLASS_HPP
# define FACTORY_CLASS_HPP

#include "IOperand.class.hpp"
#include "Operand.class.hpp"
#include <iostream>

class Factory {
public:
    Factory(void);
    ~Factory(void);

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	IOperand const * (Factory::*createFuncArray[NB_TYPE])(std::string const &) const = {
		&Factory::createInt8,
		&Factory::createInt16,
		&Factory::createInt32,
		&Factory::createFloat,
		&Factory::createDouble
	};

private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	Factory(Factory const & src);
	Factory & operator=(Factory const & rhs);
};

#endif