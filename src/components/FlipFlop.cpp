#include "FlipFlop.hpp"

namespace nts
{
  FlipFlop::FlipFlop(std::string const &type) : Component(type)
  {
    m_pins[0]->setMode(Pin::INPUT);  // Set
    m_pins[1]->setMode(Pin::INPUT);  // Data
    m_pins[2]->setMode(Pin::INPUT);  // Reset
    m_pins[3]->setMode(Pin::INPUT);  // Clock
    m_pins[4]->setMode(Pin::OUTPUT); // -Q
    m_pins[5]->setMode(Pin::OUTPUT); // Q
  }

  void FlipFlop::doOperation()
  {
    nts::Tristate set = m_pins[0]->getValue();
    nts::Tristate data = m_pins[1]->getValue();
    nts::Tristate reset = m_pins[2]->getValue();
    nts::Tristate clock = m_pins[3]->getValue();

    if (set == nts::UNDEFINED || reset == nts::UNDEFINED ||
        data == nts::UNDEFINED || clock == nts::UNDEFINED)
      {
	m_pins[4]->setValue(nts::UNDEFINED);
	m_pins[5]->setValue(nts::UNDEFINED);
      }
    else if (set == nts::FALSE && reset == nts::FALSE)
      {
	if (clock == nts::TRUE)
	  {
	    m_pins[4]->setValue(data == nts::TRUE ? nts::FALSE : nts::TRUE);
	    m_pins[5]->setValue(data);
	  }
      }
    else
      {
	m_pins[4]->setValue(reset);
	m_pins[5]->setValue(set);
      }
  }
}