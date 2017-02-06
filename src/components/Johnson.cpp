#include "Johnson.hpp"

namespace nts
{
  Johnson::Johnson(std::string const &type) : Component(type), m_count(0)
  {
    for (size_t i = 0; i < 10; ++i)
      {
	m_output[i] = std::make_unique<Pin>(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }
    m_output[0]->setValue(nts::TRUE);

    m_pins[0] = m_output[5].get(); // Q5
    m_pins[1] = m_output[1].get(); // Q1
    m_pins[2] = m_output[0].get(); // Q0
    m_pins[3] = m_output[2].get(); // Q2
    m_pins[4] = m_output[6].get(); // Q6
    m_pins[5] = m_output[7].get(); // Q7
    m_pins[6] = m_output[3].get(); // Q3

    m_pins_[7] = std::make_unique<Pin>(Pin::DEAD);
    m_pins[7] = m_pins_[7].get(); // DEAD

    m_pins[8] = m_output[8].get();                          // Q8
    m_pins[9] = m_output[4].get();                          // Q4
    m_pins[10] = m_output[9].get();                         // Q9
    m_pins_[11] = std::make_unique<Pin>(Pin::OUTPUT, this); //-Q5-9
    m_pins[11] = m_pins_[11].get();
    m_pins_[12] = std::make_unique<Pin>(Pin::DEAD); // DEAD
    m_pins[12] = m_pins_[12].get();
    m_pins_[13] = std::make_unique<Pin>(Pin::INPUT); // CLOCK
    m_pins[13] = m_pins_[13].get();
    m_pins_[14] = std::make_unique<Pin>(Pin::INPUT); // MASTER RESET
    m_pins[14] = m_pins_[14].get();

    m_lastClk = nts::UNDEFINED;
  }

  void Johnson::doOperation()
  {
    Tristate mr = m_pins[14]->getValue();
    Tristate clk = m_pins[13]->getValue();

    if (mr == nts::TRUE)
      {
	m_count = 0;
      }
    if (m_lastClk != nts::TRUE && clk == nts::TRUE)
      {
	for (size_t i = 0; i < 10; ++i)
	  {
	    if (i == m_count)
	      {
		m_output[i]->setValue(nts::TRUE);
	      }
	    else
	      {
		m_output[i]->setValue(nts::FALSE);
	      }
	  }
	m_pins[11]->setValue(m_count < 5 ? nts::TRUE : nts::FALSE);
	m_count = (m_count + 1) % 10;
      }
    m_lastClk = clk;
  }
}