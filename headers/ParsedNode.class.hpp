#ifndef PARSED_NODE_CLASS_HPP
# define PARSED_NODE_CLASS_HPP

#include "Node.class.hpp"
#include "IOperand.class.hpp"

class ParsedNode {
public:
	ParsedNode(e_tk pTkInstr, e_tk pTkValue, std::string val);
    ParsedNode(ParsedNode const & src);

    ~ParsedNode(void);

    ParsedNode & operator=(ParsedNode const & rhs);

    e_tk getTkInstr(void) const;
    e_tk getTkValue(void) const;
    std::string getValue(void) const;

private:
	const e_tk _tkInstr;
	const e_tk _tkValue;
	std::string _value;
	ParsedNode(void);
};

std::ostream & operator<<(std::ostream & os, ParsedNode & pN);

#endif