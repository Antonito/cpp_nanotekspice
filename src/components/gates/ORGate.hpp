#ifndef ORGATE_HPP_
#define ORGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class ORGate : public AGate
  {
  public:
    ORGate();
    virtual ~ORGate(){};

    virtual void doOperation();
  };
}

#endif // !ORGATE_HPP_