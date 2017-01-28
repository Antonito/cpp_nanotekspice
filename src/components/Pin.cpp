#include <cassert>
#include <utility>
#include "AGate.hpp"
#include "Pin.hpp"

namespace nts
{
  Pin::Pin(Mode mode, AGate *gate)
      : m_link(std::make_pair<IComponent *, size_t>(nullptr, 0)), m_mode(mode),
        m_gate(gate), m_lastValue(nts::UNDEFINED), m_computing(false)
  {
    // Output with no associated gate
    assert(mode <= INPUT || gate != nullptr);
  }

  Pin::Pin(Pin const &)
  {
#ifdef DEBUG
    static_assert(false, "You are not supposed to copy a pin");
#endif
  }

  Pin::~Pin()
  {
  }

  Pin &Pin::operator=(Pin const &)
  {
#ifdef DEBUG
    static_assert(false, "You are not supposed to copy a pin");
#endif
    return (*this);
  }

  Pin::Mode Pin::getMode() const
  {
    return (m_mode);
  }

  nts::Tristate Pin::getValue()
  {
    if (m_mode != INPUT && m_mode != HYBRID)
      {
	throw std::logic_error("This pin is not an input pin");
      }
    if (m_link.first != nullptr && m_computing == false)
      {
	m_computing = true;
	m_lastValue = m_link.first->Compute(m_link.second);
	m_computing = false;
      }
    return (m_lastValue);
  }

  nts::Tristate Pin::getLastValue() const
  {
    return (m_lastValue);
  }

  nts::Tristate Pin::compute()
  {
    if (m_mode != OUTPUT && m_mode != HYBRID)
      {
	throw std::logic_error("This pin is not an output pin");
      }
    if (m_gate != nullptr && m_computing == false)
      {
	m_computing = true;
	m_lastValue = m_gate->doOperation();
	m_computing = false;
      }
    return (m_lastValue);
  }

  void Pin::setLink(IComponent &component, size_t pin)
  {
    m_link.first = &component;
    m_link.second = pin;
  }
}

std::ostream &operator<<(std::ostream &os, nts::Pin const &p)
{
  nts::Tristate state = p.getLastValue();

  if (state == nts::UNDEFINED)
    {
      os << "UNDEFINED";
    }
  else
    {
      os << static_cast<int>(state);
    }
  return (os);
}
