#include "UnknownComponent.hpp"

namespace nts
{
  UnknownComponent::UnknownComponent(std::string const &msg)
      : m_message("Unknown component: " + msg)
  {
  }

  UnknownComponent::UnknownComponent(UnknownComponent const &other)
      : m_message(other.m_message)
  {
  }

  UnknownComponent::~UnknownComponent() throw()
  {
  }

  UnknownComponent &UnknownComponent::operator=(UnknownComponent const &other)
  {
    if (this != &other)
      {
	m_message = other.m_message;
      }
    return (*this);
  }

  char const *UnknownComponent::what() const throw()
  {
    return (m_message.c_str());
  }
}