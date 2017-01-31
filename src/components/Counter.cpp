#include "Counter.hpp"

namespace nts
{
  Counter::Counter(std::string const &type) : Component(type), m_val(0)
  {
    for (size_t i = 0; i < 12; ++i)
      {
	m_output[i] = new Pin(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }

    m_pins[0] = m_output[11];         // Q12
    m_pins[1] = m_output[5];          // Q6
    m_pins[2] = m_output[4];          // Q5
    m_pins[3] = m_output[6];          // Q7
    m_pins[4] = m_output[3];          // Q4
    m_pins[5] = m_output[2];          // Q3
    m_pins[6] = m_output[1];          // Q2
    m_pins[7] = new Pin(Pin::DEAD);   // VSS
    m_pins[8] = m_output[0];          // Q1
    m_pins[9] = new Pin(Pin::INPUT);  // CLOCK
    m_pins[10] = new Pin(Pin::INPUT); // MASTER-RESET
    m_pins[11] = m_output[8];         // Q9
    m_pins[12] = m_output[7];         // Q8
    m_pins[13] = m_output[9];         // Q10
    m_pins[14] = m_output[10];        // Q11
    m_pins[15] = new Pin(Pin::DEAD);  // VDD

    m_lastClk = nts::UNDEFINED;
  }

  Counter::~Counter()
  {
    for (size_t i = 0; i < 12; ++i)
      delete m_output[i];
    delete m_pins[7];
    delete m_pins[9];
    delete m_pins[10];
    delete m_pins[15];
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