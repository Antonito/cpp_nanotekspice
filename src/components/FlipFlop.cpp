#include "FlipFlop.hpp"

namespace nts
{
  FlipFlop::FlipFlop(std::string const &type) : Component(type)
  {
    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[1] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[2] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[3] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[4] = std::make_unique<Pin>(Pin::OUTPUT, this);
    m_pins_[5] = std::make_unique<Pin>(Pin::OUTPUT, this);

    m_pins[0] = m_pins_[0].get(); // Set
    m_pins[1] = m_pins_[1].get(); // Data
    m_pins[2] = m_pins_[2].get(); // Reset
    m_pins[3] = m_pins_[3].get(); // Clock
    m_pins[4] = m_pins_[4].get(); // -Q
    m_pins[5] = m_pins_[5].get(); // Q
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