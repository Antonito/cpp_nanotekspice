#include "Output.hpp"

namespace nts
{
  Output::Output() : Component("Output")
  {
    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT);
    m_pins[0] = m_pins_[0].get();
  }

  Tristate Output::getValue()
  {
    return (m_pins[0]->getValue());
  }

  Tristate Output::getLastValue() const
  {
    return (m_pins[0]->getLastValue());
  }
}