#ifndef INVALIDPIN_HPP_
#define INVALIDPIN_HPP_

#include <stdexcept>
#include <string>

namespace nts
{
  class InvalidPin : public std::exception
  {
  public:
    InvalidPin(std::string const &msg = "");
    InvalidPin(InvalidPin const &other);
    ~InvalidPin() throw();

    InvalidPin &operator=(InvalidPin const &other);

    virtual char const *what() const throw();

  private:
    std::string m_message;
  };
}

#endif // !INVALIDPIN_HPP_