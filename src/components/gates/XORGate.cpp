#include "XORGate.hpp"

namespace nts
{
  XORGate::XORGate() : AGate("XOR")
  {
  }

  void XORGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();
    Tristate b = m_pins[1]->getValue();

    if (a == UNDEFINED || b == UNDEFINED)
      m_pins[2]->setValue(UNDEFINED);
    else
      m_pins[2]->setValue(a != b ? nts::TRUE : nts::FALSE);
  }
}