#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>
#include <iostream>
#include <array>
#include <utility>
#include "IComponent.hpp"
#include "Pin.hpp"

namespace nts
{
  template <size_t pinsNumber>
  class Component : public IComponent
  {
  public:
    Component(std::string const &type) : m_type(type)
    {
    }

    Component(Component const &)
    {
#ifdef DEBUG
      static_assert(false, "You are not supposed to copy component");
#endif
    }

    ~Component()
    {
    }

    Component &operator=(Component const &)
    {
#ifdef DEBUG
      static_assert(false, "You are not supposed to assign component");
#endif
      return (*this);
    }

    Pin const *operator[](size_t t)
    {
      if (t < 1 || t > pinsNumber)
	{
	  throw std::logic_error("There is no such pin");
	}
      return (m_pins[t]);
    }

    /// Compute value of the precised pin
    virtual nts::Tristate Compute(size_t pin_num_this = 1)
    {
      if (pin_num_this < 1 || pin_num_this > pinsNumber)
	{
	  throw std::logic_error("There is no such pin");
	}
      return (m_pins[pin_num_this]->compute());
    }

    /// Useful to link IComponent together
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t target)
    {
      if (pin_num_this < 1 || pin_num_this > pinsNumber)
	{
	  throw std::logic_error("There is no such pin");
	}
      m_pins[pin_num_this]->setLink(component, target);
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
    std::array<Pin *, pinsNumber> m_pins;
    std::string m_type;
  };
}

#endif // !COMPONENT_HPP_