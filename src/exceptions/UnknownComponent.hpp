#ifndef UNKNOWNCOMPONENT_HPP_
#define UNKNOWNCOMPONENT_HPP_

#include <stdexcept>

namespace nts
{
  class UnknownComponent : public std::exception
  {
  public:
    UnknownComponent(std::string const &msg);
    UnknownComponent(UnknownComponent const &other);
    virtual ~UnknownComponent() throw();

    UnknownComponent &operator=(UnknownComponent const &other);
    virtual char const *what() const throw();

  private:
    std::string m_message;
  };
}

#endif // !UNKNOWNCOMPONENT_HPP_