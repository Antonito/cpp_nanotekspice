#include "ANDGate.hpp"

namespace nts
{
  ANDGate::ANDGate() : AGate("AND")
  {
  }

  nts::Tristate ANDGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();
    Tristate b = m_pins[1]->getValue();

    if (a == UNDEFINED || b == UNDEFINED)
      {
	return (UNDEFINED);
      }
    return (static_cast<Tristate>(a == TRUE && b == TRUE));
  }
}