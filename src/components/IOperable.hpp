#ifndef IOPERABLE_HPP_
#define IOPERABLE_HPP_

#include "IComponent.hpp"

namespace nts
{
  class IOperable
  {
  public:
    virtual nts::Tristate doOperation() = 0;
  };
}

#endif // !IOPERABLE_HPP_