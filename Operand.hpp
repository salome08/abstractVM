#ifndef OPERAND_HPP
# define OPERAND_HPP

#include <iostream>
#include <string>
#include <climits>
#include <cfloat>
#include <sstream>
#include "IOperand.hpp"
#include "Exception.hpp"
#include "main.hpp"



template <typename T>
class Operand : public IOperand
{
	private:
		eOperandType 	m_type;
		int 			m_precision;
		T 				m_value;
		// std::string 	m_strValue;

	public:
		 Operand(eOperandType type, const double & value)
		{
			m_type = type;
			if (value <= opTypes[type].max){
				if (value >= opTypes[type].min)
					m_precision = opTypes[type].precision;
				else throw Exception("Underflow on a value");
			}
			else throw Exception("Overflow on a value");
			m_value = value;
			// m_strValue = s_value;
		}
		 
		 int getPrecision( void ) const 
		 {
		 	return (m_precision);
		 }

		   virtual T getValue() const {
    return (m_value);
  }

		 eOperandType getType( void ) const 
		 {
		 	return (m_type);
		 }

		   virtual std::string const &toString() const {

		    std::string *str = new std::string();

		    std::ostringstream ss;
			// ss << std::fixed;
		    if (m_type == INT8)
		      ss << (int)m_value;
		    else
		      ss << m_value;
		    str->append(ss.str());
		    return (*str);
		
		  }

		 virtual IOperand const * operator+( IOperand const & rhs ) const
		 {
		 	//ret ptr sur Ioperand resultat 
		 	IOperand *operand = NULL;
		 	eOperandType type;

		 	type = m_precision >= rhs.getPrecision() ? m_type : rhs.getType();
		 	switch (type) {
		 		case INT8:
		 			operand = new Operand<char>(type, m_value + stod(rhs.toString()));
		 			break;
		 		case INT16:
			 		operand = new Operand<short>::Operand(type,  m_value + stod(rhs.toString()));
		 			break;
		 		case INT32:
		 			operand = new Operand<int>(type,  m_value + stod(rhs.toString()));
		 			break;
		 		case FLOAT:
		 			operand = new Operand<float>(type,  m_value + stod(rhs.toString()));
		 			break;
		 		case DOUBLE:
		 			operand = new Operand<double>(type,  m_value + stod(rhs.toString()));
		 			break;							
		 	}
		 	return (operand);
		 }



		 IOperand const * operator-( IOperand const & rhs ) const
		 {
		 	//ret ptr sur Ioperand resultat 
		 	IOperand *operand = NULL;
		 	eOperandType type;

		 	type = m_precision >= rhs.getPrecision() ? m_type : rhs.getType();
		 	switch (type) {
		 		case INT8:
		 			operand = new Operand<char>(type, m_value - stod(rhs.toString()));
		 			break;
		 		case INT16:
		 			operand = new Operand<short>(type, m_value - stod(rhs.toString()));
		 			break;
		 		case INT32:
		 			operand = new Operand<int>(type, m_value - stod(rhs.toString()));
		 			break;
		 		case FLOAT:
		 			operand = new Operand<float>(type, m_value - stod(rhs.toString()));
		 			break;
		 		case DOUBLE:
		 			operand = new Operand<double>(type, m_value - stod(rhs.toString()));
		 			break;							
		 	}
		 	return (operand);
		 }
		 IOperand const * operator*( IOperand const & rhs ) const
		  {
		 	//ret ptr sur Ioperand resultat 
		 	IOperand *operand = NULL;
		 	eOperandType type;

		 	type = m_precision >= rhs.getPrecision() ? m_type : rhs.getType();
		 	switch (type) {
		 		case INT8:
		 			operand = new Operand<char>(type, m_value * stod(rhs.toString()));
		 			break;
		 		case INT16:
		 			operand = new Operand<short>(type, m_value * stod(rhs.toString()));
		 			break;
		 		case INT32:
		 			operand = new Operand<int>(type, m_value * stod(rhs.toString()));
		 			break;
		 		case FLOAT:
		 			operand = new Operand<float>(type, m_value * stod(rhs.toString()));
		 			break;
		 		case DOUBLE:
		 			operand = new Operand<double>(type, m_value * stod(rhs.toString()));
		 			break;							
		 	}
		 	return (operand);
		 }
		 
		 IOperand const * operator/( IOperand const & rhs ) const
		  {
		 	//ret ptr sur Ioperand resultat 
		 	IOperand *operand = NULL;
		 	eOperandType type;

		 	const Operand &tmp = static_cast<const Operand &>(rhs); 
		 	if (stod(tmp.toString()) == 0)
		 		throw Exception("Division by 0");
		 	type = m_precision >= rhs.getPrecision() ? m_type : rhs.getType();
		 	switch (type) {
		 		case INT8:
		 			operand = new Operand<char>(type, m_value / stod(rhs.toString()));
		 			break;
		 		case INT16:
		 			operand = new Operand<short>(type, m_value / stod(rhs.toString()));
		 			break;
		 		case INT32:
		 			operand = new Operand<int>(type, m_value / stod(rhs.toString()));
		 			break;
		 		case FLOAT:
		 			operand = new Operand<float>(type, m_value / stod(rhs.toString()));
		 			break;
		 		case DOUBLE:
		 			operand = new Operand<double>(type, m_value / stod(rhs.toString()));
		 			break;							
		 	}
		 	return (operand);
		 }

		 virtual IOperand const * operator%( IOperand const & rhs ) const
		 {
		 	//cant use modulo on double
		 	IOperand *operand = NULL;
		 	eOperandType type;
		 	const Operand &tmp = static_cast<const Operand &>(rhs);

		 	if(stol(tmp.toString()) == 0)
		 		throw Exception("Modulo by 0");
		 	type = (m_precision >= rhs.getPrecision()) ? m_type : rhs.getType();
		 	if (m_type == FLOAT || rhs.getType() == FLOAT)
		 		throw Exception("Modulo by float");
		 	else if (m_type == DOUBLE || rhs.getType() == DOUBLE)
		 		throw Exception("Modulo by double");
		 	operand = new Operand(type, (int)m_value % stoi(tmp.toString()));
		 	return (operand);
		 }

			  // std::ostream &operator<<(std::ostream &os) {
			  //   os << this->getValue();
			  //   return (os);
			  // }
};

std::ostream		&operator<<(std::ostream &os, IOperand const *rhs);
	// static	 bool operator==(IOperand const lhs, std::string rhs);


#endif