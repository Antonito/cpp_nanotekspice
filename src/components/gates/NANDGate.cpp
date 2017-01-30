#include "NANDGate.hpp"

namespace nts
{
  NANDGate::NANDGate() : AGate("NAND")
  {
  }

  void NANDGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();
    Tristate b = m_pins[1]->getValue();

    if (a == UNDEFINED || b == UNDEFINED)
      m_pins[2]->setValue(UNDEFINED);
    else
      m_pins[2]->setValue((a == TRUE && b == TRUE) ? nts::FALSE : nts::TRUE);
  }
}