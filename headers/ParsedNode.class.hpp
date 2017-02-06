#ifndef PARSED_NODE_CLASS_HPP
# define PARSED_NODE_CLASS_HPP

#include "Node.class.hpp"
#include "IOperand.class.hpp"

template <class T = int>
class ParsedNode {
public:
	ParsedNode(e_tk pTkInstr, bool pHaveValue);
    ParsedNode(ParsedNode const & src);

    ~ParsedNode(void);

    ParsedNode & operator=(ParsedNode const & rhs);

    void setValue(T val);
    void setType(eOperandType t);

    e_tk getTkInstr(void) const;
	bool getHaveValue(void) const;
    T getValue(void) const;
	eOperandType getType(void) const;

private:
	const e_tk _tkInstr;
	const bool haveValue;
	T _value;
	eOperandType _type;
	ParsedNode(void);
};

template<class T>
std::ostream & operator<<(std::ostream & os, ParsedNode<T> & pN);

#endif