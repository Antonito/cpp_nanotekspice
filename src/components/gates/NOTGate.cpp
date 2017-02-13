#include "NOTGate.hpp"

namespace nts
{

  NOTGate::NOTGate() : NOTGate("NOT")
  {
  }

  NOTGate::NOTGate(std::string const &type) : Component(type)
  {
    m_pins[0]->setMode(Pin::INPUT);
    m_pins[1]->setMode(Pin::OUTPUT, this);
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