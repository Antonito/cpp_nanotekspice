#include "AGate.hpp"

namespace nts
{
  AGate::AGate(std::string const &type) : Component(type)
  {
    m_pins[0] = new Pin(Pin::INPUT);
    m_pins[1] = new Pin(Pin::INPUT);
    m_pins[2] = new Pin(Pin::OUTPUT, this);
  }

  AGate::~AGate()
  {
    delete m_pins[0];
    delete m_pins[1];
    delete m_pins[2];
  }
}