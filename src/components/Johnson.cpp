#include "Johnson.hpp"

namespace nts
{
  Johnson::Johnson(std::string const &type) : Component(type), m_count(0)
  {
    for (size_t i = 0; i < 10; ++i)
      {
	m_output[i] = new Pin(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::FALSE);
      }
    m_output[0]->setValue(nts::TRUE);

    m_pins[0] = m_output[5];                 // Q5
    m_pins[1] = m_output[1];                 // Q1
    m_pins[2] = m_output[0];                 // Q0
    m_pins[3] = m_output[2];                 // Q2
    m_pins[4] = m_output[6];                 // Q6
    m_pins[5] = m_output[7];                 // Q7
    m_pins[6] = m_output[3];                 // Q3
    m_pins[7] = new Pin(Pin::DEAD);          // DEAD
    m_pins[8] = m_output[8];                 // Q8
    m_pins[9] = m_output[4];                 // Q4
    m_pins[10] = m_output[9];                // Q9
    m_pins[11] = new Pin(Pin::OUTPUT, this); //-Q5-9
    m_pins[12] = new Pin(Pin::DEAD);         // DEAD
    m_pins[13] = new Pin(Pin::INPUT);        // CLOCK
    m_pins[14] = new Pin(Pin::INPUT);        // MASTER RESET

    m_lastClk = nts::UNDEFINED;
  }

  Johnson::~Johnson()
  {
    for (size_t i = 0; i < 10; ++i)
      delete m_output[i];
    delete m_pins[7];
    delete m_pins[11];
    delete m_pins[12];
    delete m_pins[13];
    delete m_pins[14];
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
	m_pins[11]->setValue(m_cout < 5 ? nts::TRUE : nts::FALSE);
	m_count = (m_count + 1) % 10;
      }
    m_lastClk = clk;
  }
}