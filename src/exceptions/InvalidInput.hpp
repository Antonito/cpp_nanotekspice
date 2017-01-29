#ifndef INVALIDINPUT_HPP_
#define INVALIDINPUT_HPP_

#include <stdexcept>
#include <string>

namespace nts
{
  class InvalidInput : public std::exception
  {
  public:
    InvalidInput(std::string const &msg);
    InvalidInput(InvalidInput const &other);
    virtual ~InvalidInput() throw();

    InvalidInput &operator=(InvalidInput const &other);

    virtual char const *what() const throw();

  private:
    std::string m_message;
  };
}

#endif // !INVALIDINPUT_HPP_