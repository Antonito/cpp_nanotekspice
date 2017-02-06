#include "Counter.hpp"

namespace nts
{
  Counter::Counter(std::string const &type) : Component(type), m_val(0)
  {
    for (size_t i = 0; i < 12; ++i)
      {
	m_output[i] = std::make_unique<Pin>(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }

    m_pins[0] = m_output[11].get(); // Q12
    m_pins[1] = m_output[5].get();  // Q6
    m_pins[2] = m_output[4].get();  // Q5
    m_pins[3] = m_output[6].get();  // Q7
    m_pins[4] = m_output[3].get();  // Q4
    m_pins[5] = m_output[2].get();  // Q3
    m_pins[6] = m_output[1].get();  // Q2

    m_pins_[7] = std::make_unique<Pin>(Pin::DEAD);
    m_pins[7] = m_pins_[7].get(); // VSS

    m_pins[8] = m_output[0].get(); // Q1

    m_pins_[9] = std::make_unique<Pin>(Pin::INPUT);
    m_pins[9] = m_pins_[9].get(); // CLOCK

    m_pins_[10] = std::make_unique<Pin>(Pin::INPUT);
    m_pins[10] = m_pins_[10].get(); // MASTER-RESET

    m_pins[11] = m_output[8].get();  // Q9
    m_pins[12] = m_output[7].get();  // Q8
    m_pins[13] = m_output[9].get();  // Q10
    m_pins[14] = m_output[10].get(); // Q11

    m_pins_[15] = std::make_unique<Pin>(Pin::DEAD);
    m_pins[15] = m_pins_[15].get(); // VDD

    m_lastClk = nts::UNDEFINED;
  }

  void Counter::doOperation()
  {
    Tristate mr = m_pins[10]->getValue();
    Tristate clk = m_pins[9]->getValue();

    if (mr == nts::TRUE)
      {
	m_val = 0;
      }
    if (m_lastClk != nts::TRUE && clk == nts::TRUE)
      {
	m_val = (m_val + 1) % (1 << 13);
	for (size_t i = 0; i < 12; ++i)
	  {
	    if (m_val & (1 << i))
	      {
		m_output[i]->setValue(nts::TRUE);
	      }
	    else
	      {
		m_output[i]->setValue(nts::FALSE);
	      }
	  }
      }
    m_lastClk = clk;
  }
}