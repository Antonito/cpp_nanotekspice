#include "Output.hpp"

namespace nts
{
  Output::Output() : Component("Output")
  {
    m_pins[0] = new Pin(Pin::INPUT);
  }

  Output::~Output()
  {
    delete m_pins[0];
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