#include "FullAdder.hpp"

namespace nts
{
  FullAdder::FullAdder(std::string const &type) : Component(type)
  {
    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[1] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[2] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[3] = std::make_unique<Pin>(Pin::OUTPUT, this);
    m_pins_[4] = std::make_unique<Pin>(Pin::OUTPUT, this);

    m_pins[0] = m_pins_[0].get();
    m_pins[1] = m_pins_[1].get();
    m_pins[2] = m_pins_[2].get();
    m_pins[3] = m_pins_[3].get();
    m_pins[4] = m_pins_[4].get();
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