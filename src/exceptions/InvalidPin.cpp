#include "InvalidPin.hpp"

namespace nts
{
  InvalidPin::InvalidPin(std::string const &msg)
      : m_message("The given pin does not exist" + msg)
  {
  }

  InvalidPin::InvalidPin(InvalidPin const &other) : m_message(other.m_message)
  {
  }

  InvalidPin::~InvalidPin() throw()
  {
  }

  InvalidPin &InvalidPin::operator=(InvalidPin const &other)
  {
    if (this != &other)
      {
	m_message = other.m_message;
      }
    return (*this);
  }

  char const *InvalidPin::what() const throw()
  {
    return (m_message.c_str());
  }
}