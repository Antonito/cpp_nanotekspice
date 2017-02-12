#include "DualFlipFlop.hpp"

namespace nts
{
  DualFlipFlop::DualFlipFlop(std::string const &type) : Component(type)
  {
    // Delete unused pins (except 6 and 13)
    for (size_t i = 0; i < 13; ++i)
      {
	if (i != 6)
	  m_pins_[i].reset();
      }
    m_pins[0] = m_latch[0][6];
    m_pins[1] = m_latch[0][5];
    m_pins[2] = m_latch[0][4];
    m_pins[3] = m_latch[0][3];
    m_pins[4] = m_latch[0][2];
    m_pins[5] = m_latch[0][1];

    m_pins[7] = m_latch[1][1];
    m_pins[8] = m_latch[1][2];
    m_pins[9] = m_latch[1][3];
    m_pins[10] = m_latch[1][4];
    m_pins[11] = m_latch[1][5];
    m_pins[12] = m_latch[1][6];
  }
}