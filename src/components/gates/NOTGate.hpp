#ifndef NOTGATE_HPP_
#define NOTGATE_HPP_

#include <string>
#include "Component.hpp"
#include "IOperable.hpp"

namespace nts
{
  class NOTGate : public Component<3>, public IOperable
  {
  public:
    NOTGate(std::string const &type);
    virtual ~NOTGate();
    virtual nts::Tristate doOperation();
  };
}

#endif // !AGATE_HPP_