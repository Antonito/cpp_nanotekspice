#include "SixNot.hpp"

namespace nts
{
  SixNot::SixNot(std::string const &type) : Component(type)
  {
    // Delete all the unused pins(except 6 and 14)
    for (size_t i = 0; i < 13; ++i)
      {
	if (i != 6)
	  m_pins_[i].reset();
      }

    m_pins[0] = m_gates[1][1];
    m_pins[1] = m_gates[1][2];

    m_pins[2] = m_gates[0][1];
    m_pins[3] = m_gates[0][2];

    m_pins[4] = m_gates[2][1];
    m_pins[5] = m_gates[2][2];

    m_pins[8] = m_gates[3][1];
    m_pins[7] = m_gates[3][2];

    m_pins[10] = m_gates[4][1];
    m_pins[9] = m_gates[4][2];

    m_pins[12] = m_gates[5][1];
    m_pins[11] = m_gates[5][2];
  }
}