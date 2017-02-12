#include "Decoder.hpp"

namespace nts
{
  Decoder::Decoder(std::string const &type) : Component(type), m_count(0)
  {
    // TODO
  }

  void Decoder::doOperation()
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