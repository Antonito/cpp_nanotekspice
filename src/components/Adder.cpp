#include "Adder.hpp"

namespace nts
{
  Adder::Adder(std::string const &type) : Component(type)
  {
    m_pins[0] = m_adder[3][1]; // A4
    m_pins[1] = m_adder[2][2]; // B3
    m_pins[2] = m_adder[2][1]; // A3
    m_pins[3] = m_adder[1][2]; // B2
    m_pins[4] = m_adder[1][1]; // A2
    m_pins[5] = m_adder[0][2]; // B1
    m_pins[6] = m_adder[0][1]; // A1
    m_pins_[7] = std::make_unique<Pin>(Pin::DEAD);
    m_pins[7] = m_pins_[7].get(); // VSS
    m_pins[8] = m_adder[0][3];    // Cin
    m_pins[9] = m_adder[0][4];    // S1
    m_pins[10] = m_adder[1][4];   // S2
    m_pins[11] = m_adder[2][4];   // S3
    m_pins[12] = m_adder[3][4];   // S4
    m_pins[13] = m_adder[3][5];   // Cout
    m_pins[14] = m_adder[3][2];   // B4
    m_pins_[15] = std::make_unique<Pin>(Pin::DEAD);
    m_pins[15] = m_pins_[15].get(); // VDD

    m_adder[1].SetLink(3, m_adder[0], 5);
    m_adder[2].SetLink(3, m_adder[1], 5);
    m_adder[3].SetLink(3, m_adder[2], 5);
  }
}