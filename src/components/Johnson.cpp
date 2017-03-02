#include "Johnson.hpp"

namespace nts
{
  Johnson::Johnson(std::string const &type) : Component(type), m_count(0)
  {
    int index[] = {2, 1, 3, 6, 9, 0, 4, 5, 8, 10};

    for (size_t i = 0; i < 10; ++i)
      {
	m_output[i] = m_pins[index[i]];
	m_output[i]->setMode(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }

    m_pins[11]->setMode(Pin::OUTPUT, this); // -Q5-9
    m_pins[13]->setMode(Pin::INPUT);        // CLOCK
    m_pins[14]->setMode(Pin::INPUT);        // MASTER RESET

    m_output[0]->setValue(nts::TRUE);
    m_lastClk = nts::FALSE;
  }

  void Johnson::doOperation()
  {
    Tristate mr = m_pins[14]->getValue();
    Tristate clk = m_pins[13]->getValue();

    if (mr == nts::TRUE)
      {
	m_count = 0;
	for (size_t i = 0; i < 10; ++i)
	  {
	    m_output[i]->setValue(nts::FALSE);
	  }
      }
    else if (m_lastClk == nts::FALSE && clk == nts::TRUE)
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