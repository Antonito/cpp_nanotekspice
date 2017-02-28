#ifndef COMPONENTFACTORY_HPP_
#define COMPONENTFACTORY_HPP_

#include "IComponent.hpp"

namespace nts
{
  class ComponentFactory
  {
  public:
    ComponentFactory();
    ComponentFactory(ComponentFactory const &other);
    ~ComponentFactory();

    ComponentFactory &operator=(ComponentFactory const &other);

    IComponent *createComponent(std::string const &type,
                                std::string const &value);

  private:
    IComponent *create4001(std::string const &value) const;
    IComponent *create4008(std::string const &value) const;
    IComponent *create4011(std::string const &value) const;
    IComponent *create4013(std::string const &value) const;
    IComponent *create4017(std::string const &value) const;
    IComponent *create4030(std::string const &value) const;
    IComponent *create4040(std::string const &value) const;
    IComponent *create4069(std::string const &value) const;
    IComponent *create4071(std::string const &value) const;
    IComponent *create4081(std::string const &value) const;
    IComponent *create4094(std::string const &value) const;
    IComponent *create4514(std::string const &value) const;
    IComponent *create4801(std::string const &value) const;
    IComponent *create2716(std::string const &value) const;
    IComponent *createTrue(std::string const &value) const;
    IComponent *createFalse(std::string const &value) const;
  };
}

#endif // !COMPONENTFACTORY_HPP_