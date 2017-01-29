#include "NANDGate.hpp"

namespace nts
{
  NANDGate::NANDGate() : AGate("NAND")
  {
  }

  nts::Tristate NANDGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();
    Tristate b = m_pins[1]->getValue();

    if (a == UNDEFINED || b == UNDEFINED)
      {
	return (UNDEFINED);
      }
    return (static_cast<Tristate>(!(a == TRUE && b == TRUE)));
  }
}