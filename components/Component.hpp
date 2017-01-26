#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>
#include <iostream>
#include <array>
#include <utility>
#include "IComponent.hpp"

namespace nts
{
  template <size_t input, size_t output>
  class Component : public IComponent
  {
  public:
    Component(std::string const &name) : m_name(name)
    {
      for (std::pair<nts::IComponent *, size_t> &p : m_in)
	p = {nullptr, 1};
      for (nts::Tristate &s : m_out)
	s = nts::UNDEFINED;
      for (bool &c : m_compute)
	c = false;
    }

    Component(Component const &other) : m_in(other.m_in), m_out(other.m_out)
    {
      for (bool &c : m_compute)
	c = false;
    }

    ~Component()
    {
    }

    Component &operator=(Component const &other)
    {
      if (this != &other)
	{
	  m_in = other.m_in;
	  m_out = other.m_out;
	}
      return (*this);
    }

    /// Compute value of the precised pin
    virtual nts::Tristate Compute(size_t pin_num_this = 1) = 0;

    /// Useful to link IComponent together
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t pin_num_target) = 0;

    virtual void Dump(void) const
    {
      std::cout << m_name << ": [";
      for (nts::Tristate const &s : m_out)
	{
	  if (&s != &m_out[0])
	    std::cout << ", ";
	  std::cout << s;
	}
      std::cout << "]" << std::endl;
    }

  protected:
    std::array<std::pair<nts::IComponent *, size_t>, input> m_in;
    std::array<nts::Tristate, output> m_out;
    std::array<bool, output>          m_compute;
    std::string m_name;
  };
}

#endif // !COMPONENT_HPP_