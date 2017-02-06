#ifndef FULLADDER_HPP_
#define FULLADDER_HPP_

#include <string>
#include "Component.hpp"
#include "IOperable.hpp"
#include "Gates.hpp"

namespace nts
{
  class FullAdder : public Component<5>, public IOperable
  {
  public:
    FullAdder(std::string const &type = "Full Adder");
    virtual ~FullAdder(){};

    virtual void doOperation();
  };
}

#endif // !FULLADDER_HPP_