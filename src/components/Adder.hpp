#ifndef ADDER_HPP_
#define ADDER_HPP_

#include <string>
#include "Component.hpp"
#include "FullAdder.hpp"

namespace nts
{
  class Adder : public Component<16>
  {
  public:
    Adder(std::string const &type);
    virtual ~Adder();

  private:
    FullAdder m_adder[4];
  };
}

#endif // !ADDER_HPP_