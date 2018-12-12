#include "Exception.hpp"

Exception::Exception(std::string const& msg) throw() : m_msg(msg)
{}

Exception::~Exception() throw()
{}

const char* Exception::what() const throw(){
	return (m_msg.c_str());
}