#include "Counter.hpp"

namespace nts
{
  Counter::Counter(std::string const &type) : Component(type), m_val(0)
  {
    int index[] = {8, 6, 5, 4, 2, 1, 3, 12, 11, 13, 14, 0};

    for (size_t i = 0; i < 12; ++i)
      {
	m_output[i] = m_pins[index[i]];
	m_output[i]->setMode(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }

    m_pins[9]->setMode(Pin::INPUT);  // CLOCK
    m_pins[10]->setMode(Pin::INPUT); // MASTER RESET

    m_lastClk = nts::UNDEFINED;
  }

  void Counter::doOperation()
  {
    Tristate mr = m_pins[10]->getValue();
    Tristate clk = m_pins[9]->getValue();

    if (mr == nts::TRUE)
      {
	m_val = 0;
	for (size_t i = 0; i < 12; ++i)
	  {
	    m_output[i]->setValue(nts::FALSE);
	  }
      }
    else if (m_lastClk != nts::FALSE && clk == nts::FALSE)
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