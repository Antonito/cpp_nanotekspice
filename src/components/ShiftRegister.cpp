#include "ShiftRegister.hpp"

namespace nts
{
  ShiftRegister::ShiftRegister(std::string const &type) : Component(type)
  {
    for (size_t i = 0; i < 8; ++i)
      {
	m_output[i] = std::make_unique<Pin>(Pin::OUTPUT, this);
	m_output[i]->setValue(nts::UNDEFINED);
      }

    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT); // Strobe
    m_pins[0] = m_pins_[0].get();
    m_pins_[1] = std::make_unique<Pin>(Pin::INPUT); // Data
    m_pins[1] = m_pins_[1].get();
    m_pins_[2] = std::make_unique<Pin>(Pin::INPUT); // Clock
    m_pins[2] = m_pins_[2].get();
    m_pins[3] = m_output[0].get();                 // Q1
    m_pins[4] = m_output[1].get();                 // Q2
    m_pins[5] = m_output[2].get();                 // Q3
    m_pins[6] = m_output[3].get();                 // Q4
    m_pins_[7] = std::make_unique<Pin>(Pin::DEAD); // VSS
    m_pins[7] = m_pins_[7].get();
    m_pins_[8] = std::make_unique<Pin>(Pin::OUTPUT, this); // Qs
    m_pins[8] = m_pins_[8].get();
    m_pins_[9] = std::make_unique<Pin>(Pin::OUTPUT, this); // Q's
    m_pins[9] = m_pins_[9].get();
    m_pins[10] = m_output[7].get();                  // Q8
    m_pins[11] = m_output[6].get();                  // Q7
    m_pins[12] = m_output[5].get();                  // Q6
    m_pins[13] = m_output[4].get();                  // Q5
    m_pins_[14] = std::make_unique<Pin>(Pin::INPUT); // Enable output
    m_pins[14] = m_pins_[14].get();
    m_pins_[15] = std::make_unique<Pin>(Pin::DEAD); // VDD
    m_pins[15] = m_pins_[15].get();

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