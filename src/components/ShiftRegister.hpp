#ifndef SHIFTREGISTER_HPP_
#define SHIFTREGISTER_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class ShiftRegister : public Component<16>, public IOperable
  {
  public:
    ShiftRegister(std::string const &type);
    virtual ~ShiftRegister(){};

    virtual void doOperation();

  private:
    Pin *    m_output[8];
    Tristate m_lastClk;
  };
}

#endif // !SHIFTREGISTER_HPP_