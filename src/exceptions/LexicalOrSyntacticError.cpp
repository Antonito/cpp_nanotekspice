#include "LexicalOrSyntacticError.hpp"

namespace nts
{
  LexicalOrSyntacticError::LexicalOrSyntacticError(std::string const &msg)
      : m_message(std::string("Lexical or syntactic error: ") + msg)
  {
  }

  LexicalOrSyntacticError::LexicalOrSyntacticError(
      LexicalOrSyntacticError const &other)
      : m_message(other.m_message)
  {
  }

  LexicalOrSyntacticError::~LexicalOrSyntacticError() throw()
  {
  }

  LexicalOrSyntacticError &LexicalOrSyntacticError::
      operator=(LexicalOrSyntacticError const &other)
  {
    if (this != &other)
      {
	m_message = other.m_message;
      }
    return (*this);
  }

  char const *LexicalOrSyntacticError::what() const throw()
  {
    return (m_message.c_str());
  }
}