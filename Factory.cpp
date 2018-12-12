#include "Factory.hpp"
#include <stdlib.h>
#include <cstdlib>

Factory::Factory(){
	lst_fun[INT8] = &Factory::createInt8;
	lst_fun[INT16] = &Factory::createInt16;
	lst_fun[INT32] = &Factory::createInt32;
	lst_fun[FLOAT] = &Factory::createFloat;
	lst_fun[DOUBLE] = &Factory::createDouble;

}

Factory::~Factory() {
	for (auto elm_in_stack : m_stack) {
		delete elm_in_stack;
	}
}
Factory::Factory (Factory const & rhs)
{
	lst_fun[INT8] = &Factory::createInt8;
	lst_fun[INT16] = &Factory::createInt16;
	lst_fun[INT32] = &Factory::createInt32;
	lst_fun[FLOAT] = &Factory::createFloat;
	lst_fun[DOUBLE] = &Factory::createDouble;
	*this = rhs;
}

Factory const & Factory::operator=(Factory const & rhs)
{
	this->m_stack = rhs.m_stack;
	return *this;
}

IOperand const *Factory::createOperand( eOperandType type, std::string const & value ) const
{
	return (this->*lst_fun[type])(value);
}

IOperand const * Factory::createInt8(const std::string &value) const
{
  IOperand		*operand;

  operand = new Operand<char>(INT8, stod(value));
  return (operand);
}

IOperand const * Factory::createInt16(const std::string &value) const
{
	IOperand 	*operand;
	operand = new Operand<short>(INT16, stod(value));
	return (operand);
} 

IOperand const * Factory::createInt32(const std::string &value) const
{
	IOperand 	*operand;
	operand = new Operand<int>(INT32, stod(value));
	return (operand);
} 

IOperand const * Factory::createFloat(const std::string &value) const
{
	IOperand 	*operand;
	operand = new Operand<float>(FLOAT, stod(value));
	return (operand);
} 

IOperand const * Factory::createDouble(const std::string &value) const
{
	IOperand 	*operand;
	operand = new Operand<double>(DOUBLE, stod(value));
	return (operand);
}

Stack& Factory::setStack() { return this->m_stack; }

IOperand const * Factory::get_frontstack()  {
	if (m_stack.empty())
		return (NULL);
	return (m_stack.front());
}

void Factory::pop()
{
	if (m_stack.empty())
		throw Exception(" Instruction pop on an empty stack");
	m_stack.pop_front();
}

void Factory::push(IOperand const  *rhs)
{
	m_stack.push_front(rhs);
}

IOperand const *Factory::add()
{
	if (m_stack.size() < 2)
		throw Exception("The stack is composed of strictly less that two values");
	IOperand const * a = get_frontstack();
	pop();
	IOperand const * b = get_frontstack();
	pop();

	push(*a + *b);
 	return (get_frontstack());
}

IOperand const *Factory::sub()
{
	if (m_stack.size() < 2)
		throw Exception("The stack is composed of strictly less that two values");
	IOperand const * a = get_frontstack();
	pop();
	IOperand const * b = get_frontstack();
	pop();

	push (*a - *b);
	return(get_frontstack());
}

IOperand const * Factory::mul()
{
	if (m_stack.size() < 2)
		throw Exception("The stack is composed of strictly less that two values");
	IOperand const * a = get_frontstack();
	pop();
	IOperand const * b = get_frontstack();
	pop();

	push(*a * *b);
	return(get_frontstack());
}

IOperand const * Factory::div()
{
	if (m_stack.size() < 2)
		throw Exception("The stack is composed of strictly less that two values");
	IOperand const * a = get_frontstack();
	pop();
	IOperand const * b = get_frontstack();
	pop();

	push(*b / *a);
	return(get_frontstack());
}

IOperand const * Factory::mod()
{
	if (m_stack.size() < 2)
		throw Exception("The stack is composed of strictly less that two values");
	IOperand const * a = get_frontstack();
	pop();
	IOperand const * b = get_frontstack();
	pop();

	push(*b % *a);
	return(get_frontstack());
}

void Factory::print()
{
	if (m_stack.empty())
		throw Exception("Print on empty stack");
	if(get_frontstack()->getType() == INT8)
	{
		std::string str = get_frontstack()->toString();
		std::string::size_type sz;
			int num = std::stoi(str,&sz);
		printf("%c\n", (char)(num));

	}
	else throw Exception("An assert instruction is not true");
}

void Factory::dump()
{
	for (auto elm_in_stack : m_stack)
        	std::cout << elm_in_stack << "\n";
}
