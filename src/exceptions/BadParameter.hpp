#ifndef BADPARAMETER_HPP_
#define BADPARAMETER_HPP_

#include <stdexcept>
#include <string>

namespace nts
{
  class BadParameter : public std::exception
  {
  public:
    BadParameter(std::string const &msg = "");
    BadParameter(BadParameter const &other);
    ~BadParameter() throw();

    BadParameter &operator=(BadParameter const &other);

    char const *what() const throw();

  private:
    std::string m_message;
  };
}

#endif // !BADPARAMETER_HPP_