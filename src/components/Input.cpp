#include "Input.hpp"

namespace nts
{
  Input::Input(InputType type, std::string const &value)
      : Component("input"), m_type(type)
  {
    if (value != "")
      throw std::logic_error("An input doesn't need a value parameter");
    m_pins[0] = new Pin(Pin::OUTPUT, this);
  }

  Input::~Input()
  {
    delete m_pins[0];
  }

  void Input::changeValue(Tristate val)
  {
    if (m_type == INPUT)
      m_value = val;
    else
      throw std::logic_error("You cannot set the value of a clock");
  }

  void Input::setValue(Tristate val)
  {
    m_value = val;
  }

  void Input::update()
  {
    if (m_type == InputType::CLOCK)
      {
	if (m_value == TRUE)
	  m_value = FALSE;
	else if (m_value == FALSE)
	  m_value = TRUE;
      }
  }

  Tristate Input::doOperation()
  {
    return (m_value);
  }
}