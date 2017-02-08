#ifndef VIRTUAL_MACHINE_HPP
# define VIRTUAL_MACHINE_HPP

class VirtualMachine {
public:
    VirtualMachine(void);
    VirtualMachine(VirtualMachine const & src);

    virtual ~VirtualMachine(void);

    VirtualMachine & operator=(VirtualMachine const & rhs);
};

#endif