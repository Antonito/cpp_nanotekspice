#ifndef LEXICALORSYNTACTICERROR_HPP_
#define LEXICALORSYNTACTICERROR_HPP_

#include <stdexcept>

namespace nts
{
  class LexicalOrSyntacticError : public std::exception
  {
  public:
    LexicalOrSyntacticError(std::string const &msg = "");
    LexicalOrSyntacticError(LexicalOrSyntacticError const &other);
    virtual ~LexicalOrSyntacticError() throw();

    LexicalOrSyntacticError &operator=(LexicalOrSyntacticError const &other);

    virtual char const *what() const throw();

  private:
    std::string m_message;
  };
}

#endif // !LEXICALORSYNTACTICERROR_HPP_