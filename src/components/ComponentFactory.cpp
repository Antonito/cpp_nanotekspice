#include <stdexcept>
#include <string>
#include "ANDGate.hpp"
#include "QuadGate.hpp"
#include "ComponentFactory.hpp"

namespace nts
{
  ComponentFactory::ComponentFactory()
  {
  }

  ComponentFactory::ComponentFactory(ComponentFactory const &)
  {
  }

  ComponentFactory::~ComponentFactory()
  {
  }

  ComponentFactory &ComponentFactory::operator=(ComponentFactory const &)
  {
    return (*this);
  }

  IComponent *ComponentFactory::createComponent(std::string const &type,
                                                std::string const &value)
  {

    IComponent *(ComponentFactory::*tab[])(std::string const &)const = {
        &ComponentFactory::create4081};
    std::string types[] = {"4081"};

    // Check if there are same count of elements in tab and types
    static_assert(sizeof(tab) / sizeof(tab[0]) ==
                      sizeof(types) / sizeof(types[0]),
                  "Not the same amount of elements in tab and types");

    for (size_t i = 0; i < sizeof(tab) / sizeof(tab[0]); ++i)
      {
	if (types[i] == type)
	  return ((this->*tab[i])(value));
      }
    return (nullptr);
  }

  IComponent *ComponentFactory::create4081(std::string const &value) const
  {
    if (value != "")
      {
	throw std::logic_error("4081 chipset doesn't need input value");
      }
    return (new QuadGate<ANDGate>("4081"));
  }
}