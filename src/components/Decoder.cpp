#include "Decoder.hpp"

namespace nts
{
  Decoder::Decoder(std::string const &type) : Component(type), m_count(0)
  {
    int out[] = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};
    int in[] = {2, 3, 21, 22};

    for (size_t i = 0; i < 16; ++i)
      {
	m_output[i] = m_pins[out[i] - 1];
	m_output[i]->setMode(Pin::OUTPUT, this)
      }

    for (size_t i = 0; i < 4; ++i)
      {
	m_input[i] = m_pins[in[i] - 1];
	m_input[i]->setMode(Pin::INPUT, this);
      }

    m_strobe = m_pins[0];
    m_inhibit = m_pins[22];

    m_strobe->setMode(Pin::INPUT);
    m_inhibit->setMode(Pin::INPUT);
  }

  void Decoder::doOperation()
  {
    Tristate strobe = m_strobe->getValue();
    Tristate inhibit = m_inhibit->getValue();

    // Strobe = 1
    if (strobe == nts::TRUE)
      {
	// Inhibit = 1
	if (m_inhibit == nts::TRUE)
	  {
	    // Set all output to 0
	    for (size_t i = 0; i < 16; ++i)
	      {
		m_output->setValue(nts::FALSE);
	      }
	  }
	// Inhibit = 0
	else if (m_inhibit == nts::FALSE)
	  {
	    size_t sum = 0;

	    // Get the binary sum
	    for (size_t i = 0; i < 4; ++i)
	      {
		if (m_input[i] == nts::TRUE)
		  {
		    sum += 1 << i;
		  }
	      }

	    // Set the right one to 1
	    for (size_t i = 0; i < 16; ++i)
	      {
		m_output->setValue((i == sum) ? nts::TRUE : nts::FALSE);
	      }
	  }
      }
  }
}