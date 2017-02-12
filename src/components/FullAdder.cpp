#include "FullAdder.hpp"

namespace nts
{
  FullAdder::FullAdder(std::string const &type) : Component(type)
  {
    m_pins[0]->setMode(Pin::INPUT);
    m_pins[1]->setMode(Pin::INPUT);
    m_pins[2]->setMode(Pin::INPUT);
    m_pins[3]->setMode(Pin::INPUT);
    m_pins[4]->setMode(Pin::OUTPUT);
  }

  void FullAdder::doOperation()
  {
    int           count = 0;
    nts::Tristate a = m_pins[0]->getValue();
    nts::Tristate b = m_pins[1]->getValue();
    nts::Tristate c = m_pins[2]->getValue();

    if (a == nts::UNDEFINED || b == nts::UNDEFINED || c == nts::UNDEFINED)
      {
	m_pins[3]->setValue(nts::UNDEFINED);
	m_pins[4]->setValue(nts::UNDEFINED);
	return;
      }

    count += (a == nts::TRUE) ? 1 : 0;
    count += (b == nts::TRUE) ? 1 : 0;
    count += (c == nts::TRUE) ? 1 : 0;

    m_pins[3]->setValue((count & 1) ? nts::TRUE : nts::FALSE);
    m_pins[4]->setValue((count & 2) ? nts::TRUE : nts::FALSE);
  }
}