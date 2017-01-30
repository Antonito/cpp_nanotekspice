#include "FullAdder.hpp"

namespace nts
{
  FullAdder::FullAdder(std::string const &type) : Component(type)
  {
    // Inputs
    m_pins[0] = m_node[0][1]; // A
    m_pins[1] = m_node[1][1]; // B
    m_pins[2] = m_node[2][1]; // Cin

    // Xor 1
    m_xor[0].SetLink(1, m_node[0], 2);
    m_xor[0].SetLink(2, m_node[1], 2);

    // Xor 2
    m_xor[1].SetLink(1, m_xor[0], 3);
    m_xor[1].SetLink(2, m_node[2], 2);

    // And 1
    m_and[0].SetLink(1, m_node[2], 2);
    m_and[0].SetLink(2, m_xor[0], 3);

    // And 2
    m_and[1].SetLink(1, m_node[0], 2);
    m_and[1].SetLink(2, m_node[1], 2);

    // Or
    m_or.SetLink(1, m_and[0], 3);
    m_or.SetLink(2, m_and[1], 3);

    // Outputs
    m_pins[3] = m_xor[1][3]; // S
    m_pins[4] = m_or[3];     // Cout
  }

  FullAdder::~FullAdder()
  {
  }
}