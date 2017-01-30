#include "Input.hpp"
#include "BadParameter.hpp"

namespace nts
{
  Input::Input(InputType type, std::string const &value)
      : Component("input"), m_type(type)
  {
    if (value != "")
      throw BadParameter("An input doesn't need a value parameter");
    m_pins[0] = new Pin(Pin::OUTPUT, this);
    m_value = nts::UNDEFINED;
    // m_pins[0]->compute();
  }

  Input::~Input()
  {
    delete m_pins[0];
  }

  void Input::changeValue(Tristate val)
  {
    if (m_type == InputType::INPUT)
      {
	m_value = val;
	m_pins[0]->compute();
      }
    else
      throw BadParameter("You cannot set the value of a clock");
  }

  void Input::setValue(Tristate val)
  {
    m_value = val;
    m_pins[0]->compute();
  }

  void Input::update()
  {
    if (m_type == InputType::CLOCK)
      {
	if (m_value == TRUE)
	  m_value = FALSE;
	else if (m_value == FALSE)
	  m_value = TRUE;
	m_pins[0]->compute();
      }
  }

  void Input::doOperation()
  {
    m_pins[0]->setValue(m_value);
  }
}