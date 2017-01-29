#include "NOTGate.hpp"

namespace nts
{
  NOTGate::NOTGate(std::string const &type) : Component(type)
  {
    m_pins[0] = new Pin(Pin::INPUT);
    m_pins[1] = new Pin(Pin::OUTPUT, this);
  }

  NOTGate::~NOTGate()
  {
    delete m_pins[0];
    delete m_pins[1];
  }

  nts::Tristate NOTGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();

    if (a == UNDEFINED)
      {
	return (UNDEFINED);
      }
    return (a == nts::TRUE ? nts::FALSE : nts::TRUE);
  }
}