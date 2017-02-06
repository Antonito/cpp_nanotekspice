#include "NOTGate.hpp"

namespace nts
{
  NOTGate::NOTGate(std::string const &type) : Component(type)
  {
    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[1] = std::make_unique<Pin>(Pin::OUTPUT, this);

    m_pins[0] = m_pins_[0].get();
    m_pins[1] = m_pins_[1].get();
  }

  void NOTGate::doOperation()
  {
    Tristate a = m_pins[0]->getValue();

    if (a == UNDEFINED)
      m_pins[1]->setValue(UNDEFINED);
    else
      m_pins[1]->setValue(a == TRUE ? nts::FALSE : nts::TRUE);
  }
}