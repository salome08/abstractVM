#include <iostream>
#include "Operand.hpp"


std::ostream &operator<<(std::ostream &o, IOperand const *rhs) {
    o << rhs->toString();
    return (o);
}
