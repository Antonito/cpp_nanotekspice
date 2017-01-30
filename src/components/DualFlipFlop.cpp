#include "DualFlipFlop.hpp"

namespace nts
{
  DualFlipFlop::DualFlipFlop(std::string const &type) : Component(type)
  {
    m_pins[0] = m_latch[0][6];
    m_pins[1] = m_latch[0][5];
    m_pins[2] = m_latch[0][4];
    m_pins[3] = m_latch[0][3];
    m_pins[4] = m_latch[0][2];
    m_pins[5] = m_latch[0][1];
    m_pins[6] = new Pin(Pin::DEAD);
    m_pins[7] = m_latch[1][1];
    m_pins[8] = m_latch[1][2];
    m_pins[9] = m_latch[1][3];
    m_pins[10] = m_latch[1][4];
    m_pins[11] = m_latch[1][5];
    m_pins[12] = m_latch[1][6];
    m_pins[13] = new Pin(Pin::DEAD);
  }

  DualFlipFlop::~DualFlipFlop()
  {
    delete m_pins[6];
    delete m_pins[13];
  }
}