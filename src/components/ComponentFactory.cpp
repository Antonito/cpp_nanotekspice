#include <stdexcept>
#include <string>
#include "ANDGate.hpp"
#include "ORGate.hpp"
#include "NANDGate.hpp"
#include "NORGate.hpp"
#include "XORGate.hpp"
#include "NOTGate.hpp"
#include "QuadGate.hpp"
#include "ComponentFactory.hpp"
#include "BadParameter.hpp"

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
        &ComponentFactory::create4001, &ComponentFactory::create4008,
        &ComponentFactory::create4011, &ComponentFactory::create4013,
        &ComponentFactory::create4017, &ComponentFactory::create4030,
        &ComponentFactory::create4040, &ComponentFactory::create4069,
        &ComponentFactory::create4071, &ComponentFactory::create4081,
        &ComponentFactory::create4094, &ComponentFactory::create4514,
        &ComponentFactory::create4801, &ComponentFactory::create2716};
    std::string types[] = {"4001", "4008", "4011", "4013", "4017",
                           "4030", "4040", "4069", "4071", "4081",
                           "4094", "4514", "4801", "2716"};

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

  // 4001 Four NOR gates
  IComponent *ComponentFactory::create4001(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4001 chipset doesn't need input value");
      }
    return (new QuadGate<NORGate>("4001"));
  }

  // 4008 4 bits adder
  IComponent *ComponentFactory::create4008(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4008 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4011 Four NAND gates
  IComponent *ComponentFactory::create4011(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4011 chipset doesn't need input value");
      }
    return (new QuadGate<NANDGate>("4011"));
  }

  // 4013 Dual flip flop
  IComponent *ComponentFactory::create4013(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4013 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4017 10bits Johnson decade
  IComponent *ComponentFactory::create4017(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4017 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4030 Four XOR gates
  IComponent *ComponentFactory::create4030(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4030 chipset doesn't need input value");
      }
    return (new QuadGate<NORGate>("4030"));
  }

  // 4040 12bits counter
  IComponent *ComponentFactory::create4040(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4040 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4069 Six NOT gates
  IComponent *ComponentFactory::create4069(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4069 chipset doesn't need input value");
      }
    return (nullptr); // TODO: create 4069 type
  }

  // 4071 Four OR gates
  IComponent *ComponentFactory::create4071(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4071 chipset doesn't need input value");
      }
    return (new QuadGate<ORGate>("4071"));
  }

  // 4081 Four AND gates
  IComponent *ComponentFactory::create4081(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4081 chipset doesn't need input value");
      }
    return (new QuadGate<ANDGate>("4081"));
  }

  // 4094 8bits shift register
  IComponent *ComponentFactory::create4094(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4094 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4514 4bits decoder
  IComponent *ComponentFactory::create4514(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4514 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 4801 RAM
  IComponent *ComponentFactory::create4801(std::string const &value) const
  {
    if (value != "")
      {
	throw BadParameter("4801 chipset doesn't need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }

  // 2716 ROM
  IComponent *ComponentFactory::create2716(std::string const &value) const
  {
    if (value == "")
      {
	throw BadParameter("2716 chipset need input value");
      }
    throw std::exception();
    return (nullptr); // TODO: implement
  }
}