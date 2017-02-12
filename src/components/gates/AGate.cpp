#include "AGate.hpp"

namespace nts
{
  AGate::AGate(std::string const &type) : Component(type)
  {
    m_pins[0]->setMode(Pin::INPUT);
    m_pins[1]->setMode(Pin::INPUT);
    m_pins[2]->setMode(Pin::OUTPUT, this);
  }
}