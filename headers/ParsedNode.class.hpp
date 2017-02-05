#ifndef PARSED_NODE_CLASS_HPP
# define PARSED_NODE_CLASS_HPP

#include "Node.class.hpp"

enum e_type {
	INT_8,
	INT_16,
	INT_32,
	FLOAT,
	DOUBLE,
};

template <typename T>
class ParsedNode {
public:
	ParsedNode(e_tk pTkInstr, bool pHaveValue);
    ParsedNode(ParsedNode const & src);

    ~ParsedNode(void);

    ParsedNode & operator=(ParsedNode const & rhs);

    void setValue(T val);
    void setType(e_type t);

    e_tk getTkInstr(void) const;
	bool getHaveValue(void) const;
    T getValue(void) const;
	e_type getType(void) const;

private:
	const e_tk _tkInstr;
	const bool haveValue;
	T _value;
	e_type _type;
	ParsedNode(void);
};

template<class T>
std::ostream & operator<<(std::ostream & os, ParsedNode<T> & pN);

#endif