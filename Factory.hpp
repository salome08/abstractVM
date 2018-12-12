#ifndef FACTORY_HPP
# define FACTORY_HPP

#include <iostream>
#include <string>
#include <list>
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Exception.hpp"

typedef std::list<const IOperand *> Stack;

class Factory
{
public:
	Factory();
	~Factory();
	
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	Stack& setStack();	
	IOperand const * get_frontstack() ;
	void pop();
	void push(IOperand const *rhs);
	IOperand const *add();
	IOperand const *sub();
	IOperand const *mul();
	IOperand const *div();
	IOperand const *mod();
	void print();

	void dump();


private:
	typedef IOperand const *(Factory::*funcptr)(std::string const & value) const;

	funcptr lst_fun[5];
	Stack m_stack;
	Factory (Factory const & rhs);
	Factory const & operator=(Factory const & rhs);
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;




};

#endif