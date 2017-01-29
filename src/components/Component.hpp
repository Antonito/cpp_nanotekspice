#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>
#include <iostream>
#include <array>
#include <utility>
#include "IComponent.hpp"
#include "Pin.hpp"
#include "InvalidPin.hpp"

namespace nts
{
  template <size_t pinsNumber>
  class Component : public IComponent
  {
  public:
    Component(Component const &) = delete;
    virtual ~Component(){};

    Component &operator=(Component const &) = delete;

    Pin *&operator[](size_t t)
    {
      if (t < 1 || t > pinsNumber)
	{
	  throw InvalidPin(
	      "Accessing component's pin with bad index (operatorp[])");
	}
      return (m_pins[t - 1]);
    }

    /// Compute value of the precised pin
    virtual nts::Tristate Compute(size_t pin_num_this = 1)
    {
      if (pin_num_this < 1 || pin_num_this > pinsNumber)
	{
	  throw InvalidPin("Trying to compute an invalid pin");
	}
      return (m_pins[pin_num_this - 1]->compute());
    }

    /// Useful to link IComponent together
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t target)
    {
      if (pin_num_this < 1 || pin_num_this > pinsNumber)
	{
	  throw InvalidPin("Trying to link an invalid pin");
	}
      m_pins[pin_num_this - 1]->setLink(component, target);
    }

    virtual void Dump(void) const
    {
      std::cout << "[" << m_type << "] : [";
      for (size_t i = 0; i < pinsNumber; ++i)
	{
	  if (i != 0)
	    std::cout << ", ";
	  std::cout << *m_pins[i];
	}
      std::cout << "]" << std::endl;
    }

  protected:
    Component(std::string const &type) : m_type(type)
    {
    }

    std::array<Pin *, pinsNumber> m_pins;
    std::string m_type;
  };
}

#endif // !COMPONENT_HPP_