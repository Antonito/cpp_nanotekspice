#include "RAM.hpp"

namespace nts
{
  RAM::RAM(std::string const &type) : Component(type), m_buff()
  {
    int addrIn[] = {7, 6, 5, 4, 3, 2, 1, 0, 22, 21};
    int dataIO[] = {8, 9, 10, 12, 13, 14, 15, 16};

    for (size_t i = 0; i < 10; ++i)
      {
	m_addrInput[i] = m_pins[addrIn[i]];
	m_addrInput[i]->setMode(Pin::INPUT);
      }
    for (size_t i = 0; i < 8; ++i)
      {
	m_dataIO[i] = m_pins[dataIO[i]];
	m_dataIO[i]->setMode(Pin::HYBRID, this);
	m_dataIO[i]->setValue(Tristate::FALSE);
      }
    m_writeEnable = m_pins[20];
    m_outputEnable = m_pins[19];
    m_noConnect = m_pins[18];
    m_chipEnable = m_pins[17];
    m_chipEnable->setMode(Pin::INPUT);
    m_noConnect->setMode(Pin::INPUT);
    m_outputEnable->setMode(Pin::INPUT);
    m_writeEnable->setMode(Pin::INPUT);
  }

  void RAM::doOperation()
  {
    int          x = 0;
    int          y = 0;
    std::uint8_t requ_byte;

    y |= m_addrInput[1]->getValue() | (m_addrInput[5]->getValue() << 1) |
         (m_addrInput[8]->getValue() << 2);
    x |= m_addrInput[0]->getValue() | (m_addrInput[2]->getValue() << 1) |
         (m_addrInput[3]->getValue() << 2) |
         (m_addrInput[4]->getValue() << 3) |
         (m_addrInput[6]->getValue() << 4) |
         (m_addrInput[7]->getValue() << 5) | (m_addrInput[9]->getValue() << 6);
    requ_byte = m_buff[(y * 128 + x)];
    if (!m_chipEnable->getValue())
      {
	// Mode DESELECT
	for (size_t i = 0; i < 8; ++i)
	  {
	    m_dataIO[i]->setValue(nts::UNDEFINED);
	  }
      }
    else
      {
	if (m_writeEnable->getValue())
	  {
	    // Mode Write
	    requ_byte = 0;
	    for (size_t i = 0; i < 8; ++i)
	      {
		requ_byte |= m_dataIO[i]->getValue() << i;
	      }
	    m_buff[(y * 128 + x)] = requ_byte;
	  }
	else if (!m_outputEnable->getValue())
	  {
	    // High Z
	    for (size_t i = 0; i < 8; ++i)
	      {
		m_dataIO[i]->setValue(nts::UNDEFINED);
	      }
	  }
	else
	  {
	    // Mode Read
	    for (size_t i = 0; i < 8; ++i)
	      {
		m_dataIO[i]->setValue(((requ_byte & (1 << i)) != 0)
		                          ? nts::Tristate::TRUE
		                          : nts::Tristate::FALSE);
	      }
	  }
      }
  }
}
