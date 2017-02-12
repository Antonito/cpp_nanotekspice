#include "Output.hpp"

namespace nts
{
  Output::Output() : Component("Output")
  {
    m_pins[0]->setMode(Pin::INPUT);
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