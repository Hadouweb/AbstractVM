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

    void setValue(IOperand * val);

    e_tk getTkInstr(void) const;
	bool getHaveValue(void) const;
    IOperand * getValue(void) const;

private:
	const e_tk _tkInstr;
	const bool haveValue;
	IOperand * _value;
	ParsedNode(void);
};

template<class T>
std::ostream & operator<<(std::ostream & os, ParsedNode<T> & pN);

#endif