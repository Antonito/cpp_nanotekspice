#ifndef QUADGATE_HPP_
#define QUADGATE_HPP_

#include <type_traits>
#include "Component.hpp"
#include "AGate.hpp"

namespace nts
{
  template <typename T>
  class QuadGate : public Component<14>
  {
    static_assert(std::is_base_of<AGate, T>::value, "T must be a AGate!");

  public:
    QuadGate(std::string const &type) : Component(type)
    {
      m_pins[0] = m_gates[0][1];
      m_pins[1] = m_gates[0][2];
      m_pins[2] = m_gates[0][3];

      m_pins[3] = m_gates[1][3];
      m_pins[4] = m_gates[1][2];
      m_pins[5] = m_gates[1][1];

      m_pins_[6] = std::make_unique<Pin>(Pin::DEAD);
      m_pins[6] = m_pins_[6].get();

      m_pins[7] = m_gates[2][1];
      m_pins[8] = m_gates[2][2];
      m_pins[9] = m_gates[2][3];

      m_pins[10] = m_gates[3][3];
      m_pins[11] = m_gates[3][2];
      m_pins[12] = m_gates[3][1];

      m_pins_[13] = std::make_unique<Pin>(Pin::DEAD);
      m_pins[13] = m_pins_[13].get();
    }

  private:
    std::array<T, 4> m_gates;
  };
}

#endif // !QUADGATE_HPP_