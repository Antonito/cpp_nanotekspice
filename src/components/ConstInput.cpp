#include "ConstInput.hpp"

namespace nts
{
  ConstInput::ConstInput(std::string const &type, Tristate res)
      : Component(type), m_res(res)
  {
    m_pins[0]->setMode(Pin::OUTPUT, this);
  }

  void ConstInput::doOperation()
  {
    m_pins[0]->setValue(m_res);
  }
}