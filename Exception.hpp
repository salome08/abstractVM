#ifndef EXEPTION_HPP
# define EXEPTION_HPP

#include <string>
#include <exception>

class Exception : public std::exception
{
public: 
	Exception(std::string const& msg) throw();
	virtual ~Exception() throw();

	virtual const char* what() const throw();
private:
	std::string  m_msg;
};
#endif