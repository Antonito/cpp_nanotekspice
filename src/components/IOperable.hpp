#ifndef IOPERABLE_HPP_
#define IOPERABLE_HPP_

#include "IComponent.hpp"

namespace nts
{
  class IOperable
  {
  public:
    virtual void doOperation() = 0;
  };
}

#endif // !IOPERABLE_HPP_