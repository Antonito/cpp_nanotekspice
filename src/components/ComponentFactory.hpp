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
    IComponent *create4081(std::string const &value) const;
  };
}

#endif // !COMPONENTFACTORY_HPP_