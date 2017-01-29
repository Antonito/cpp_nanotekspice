#include "BadParameter.hpp"

namespace nts
{
  BadParameter::BadParameter(std::string const &msg)
      : m_message("Bad parameter: " + msg)
  {
  }

  BadParameter::BadParameter(BadParameter const &other)
      : m_message(other.m_message)
  {
  }

  BadParameter::~BadParameter() throw()
  {
  }

  BadParameter &BadParameter::operator=(BadParameter const &other)
  {
    if (this != &other)
      {
	m_message = other.m_message;
      }
    return (*this);
  }

  char const *BadParameter::what() const throw()
  {
    return (m_message.c_str());
  }
}