#include "ShiftRegister.hpp"

namespace nts
{
  ShiftRegister::ShiftRegister(std::string const &type) : Component(type)
  {
    int index[] = {3, 4, 5, 6, 13, 12, 11, 10};

    for (size_t i = 0; i < 8; ++i)
      {
	m_output[i] = m_pins[index[i]];
	m_output[i]->setMode(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::UNDEFINED);
      }

    m_pins[0]->setMode(Pin::INPUT);        // Strobe
    m_pins[1]->setMode(Pin::INPUT);        // Data
    m_pins[2]->setMode(Pin::INPUT);        // Clock
    m_pins[8]->setMode(Pin::OUTPUT, this); // Qs
    m_pins[9]->setMode(Pin::OUTPUT, this); // Q's
    m_pins[14]->setMode(Pin::INPUT);       // Enable output

    m_lastClk = nts::UNDEFINED;
  }

  void ShiftRegister::doOperation()
  {
    Tristate clk = m_pins[2]->getValue();        // Clock
    Tristate outEnable = m_pins[14]->getValue(); // Output Enable
    Tristate strobe = m_pins[0]->getValue();     // Strobe
    Tristate data = m_pins[1]->getValue();       // Data

    if (outEnable == nts::TRUE && clk != nts::UNDEFINED)
      {
	if (clk == nts::TRUE)
	  {
	    m_pins[8]->setValue(m_pins[11]->getLastValue());
	  }
	else if (clk == nts::FALSE)
	  {
	    m_pins[9]->setValue(m_pins[11]->getLastValue());
	  }
	for (size_t i = 0; i < 8; ++i)
	  {
	    m_output[i]->setValue(nts::UNDEFINED);
	  }
      }
    else if (clk == nts::TRUE && outEnable == nts::TRUE &&
             strobe != nts::UNDEFINED)
      {
	if (strobe == nts::FALSE)
	  {
	    m_pins[8]->setValue(m_pins[11]->getLastValue());
	  }
	else if (data != nts::UNDEFINED)
	  {
	    m_pins[8]->setValue(m_pins[11]->getLastValue());
	    for (size_t i = 0; i < 7; ++i)
	      {
		m_output[i + 1]->setValue(m_output[i]->getValue());
	      }
	    m_output[0]->setValue(data);
	  }
      }
    else if (clk == nts::FALSE && outEnable == nts::TRUE &&
             strobe == nts::TRUE && data == nts::TRUE)
      {
	m_pins[9]->setValue(m_pins[11]->getLastValue());
      }

    m_lastClk = clk;
  }
}