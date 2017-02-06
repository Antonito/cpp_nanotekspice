#include "AGate.hpp"

namespace nts
{
  AGate::AGate(std::string const &type) : Component(type)
  {
    m_pins_[0] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[1] = std::make_unique<Pin>(Pin::INPUT);
    m_pins_[2] = std::make_unique<Pin>(Pin::OUTPUT, this);

    m_pins[0] = m_pins_[0].get();
    m_pins[1] = m_pins_[1].get();
    m_pins[2] = m_pins_[2].get();
  }
}