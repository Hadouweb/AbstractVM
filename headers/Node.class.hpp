#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

#include "Lexer.class.hpp"

class Node {
public:
    Node(void);
    Node(Node const & src);

    ~Node(void);

    Node & operator=(Node const & rhs);

private:
	e_tk_instr _token;
};

#endif