#include "InvalidInput.hpp"

namespace nts
{
  InvalidInput::InvalidInput(std::string const &msg)
      : m_message("Invalid input: " + msg)
  {
  }

  InvalidInput::InvalidInput(InvalidInput const &other)
      : m_message(other.m_message)
  {
  }

  InvalidInput::~InvalidInput() throw()
  {
  }

  InvalidInput &InvalidInput::operator=(InvalidInput const &other)
  {
    if (this != &other)
      {
	m_message = other.m_message;
      }
    return (*this);
  }

  char const *InvalidInput::what() const throw()
  {
    return (m_message.c_str());
  }
}
