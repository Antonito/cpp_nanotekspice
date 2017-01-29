#include "Output.hpp"

namespace nts
{
  Output::Output() : Component("Output")
  {
    m_pins[0] = new Pin(Pin::HYBRID, this);
  }

  Output::~Output()
  {
    delete m_pins[0];
  }

  Tristate Output::doOperation()
  {
    return (m_pins[0]->getValue());
  }
}